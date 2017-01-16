#include <stdexcept>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <csignal>
#include <Debug.hpp>
#include <json/json.hpp>
#include "SerialReceiver.hpp"

using namespace nlohmann;

int SerialReceiver::set_interface_attribs(int fd, int speed, int parity)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if (tcgetattr(fd, &tty) != 0)
	{
		printf("error %d from tcgetattr", errno);
		return -1;
	}

	cfsetospeed(&tty, speed);
	cfsetispeed(&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
													// disable IGNBRK for mismatched speed tests; otherwise receive break
													// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // disable break processing
	tty.c_lflag = 0;                // no signaling chars, no echo,
									// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN] = 0;            // read doesn't block
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
									// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		printf("error %d from tcsetattr", errno);
		return -1;
	}
	return 0;
}

void SerialReceiver::set_blocking(int fd, int should_block)
{
	struct termios tty;
	memset(&tty, 0, sizeof tty);
	if (tcgetattr(fd, &tty) != 0)
	{
		printf("error %d from tggetattr", errno);
		return;
	}

	tty.c_cc[VMIN] = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr(fd, TCSANOW, &tty) != 0)
	{
		printf("error %d setting term attributes", errno);
	}
}

SerialReceiver::SerialReceiver(Device* setup)
	: setup(setup), msg_queue("serialqueue"),
	serial_fd(0), serial_buffer_pos(0)
{
	DEBUG_MSG("SerialReceiver::SerialReceiver");
	if (setup == NULL)
	{
		throw std::runtime_error("setup == NULL");
	}

        std::string portname("/dev/ttyACM0");
	serial_fd = open(portname.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
	if (serial_fd < 0)
	{
		printf("error %d opening %s: %s", errno, portname.c_str(), strerror(errno));
		throw std::runtime_error("serial problem");
	}

	set_interface_attribs(serial_fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking(serial_fd, 0);                // set no blocking

	async_reader = std::thread(&SerialReceiver::ReceiverThread, this);
}

volatile extern sig_atomic_t done;

SerialReceiver::~SerialReceiver()
{
	done = 1;
}

void SerialReceiver::ReceiverThread()
{
	DEBUG_MSG("SerialReceiver::ReceiverThread");
	SharedMemoryQueueMessage message;
	while (!done)
	{
		int bytes_avail;
		ioctl(serial_fd, FIONREAD, &bytes_avail);
		if (bytes_avail > 0 && (size_t)serial_buffer_pos < (sizeof(serial_buffer) - bytes_avail))
		{
			int n = read(serial_fd, serial_buffer + serial_buffer_pos, sizeof(serial_buffer) - serial_buffer_pos);
			if (n > 0)
			{
				serial_buffer_pos += n;
			}
		}

		if (serial_buffer_pos > 0)
		{
			for (size_t i = 0; i < (size_t)serial_buffer_pos; ++i)
			{
				if (serial_buffer[i] == '}') // end of an arduino message
				{
					int j = i + 1;
					std::string temp_str(serial_buffer, j);
					memmove(serial_buffer, serial_buffer + j, sizeof(serial_buffer) - i); // shift the buffer by the read amount of chars
					serial_buffer_pos -= j;

					message.Set(temp_str);
					if (msg_queue.Push(&message))
					{
						DEBUG_MSG("SerialReceiver::ReceiverThread:Push: SUCCESS: " << temp_str);
					}
					else
					{
						DEBUG_MSG("SerialReceiver::ReceiverThread:Push: FAILURE: " << temp_str);
					}
					i = 0;
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

void SerialReceiver::Update()
{
	static SharedMemoryQueueMessage message;
	if (msg_queue.TryPop(&message))
	{
		try
		{
			json j = json::parse(message.Get().c_str());

			std::string type_str = j.at("type").get<std::string>();
			SensorType type = SensorTypeStrings.right.at(type_str);
			size_t index = j.at("index").get<size_t>();
			double value = j.at("value").get<double>();
			Sensor* sensor = setup->GetSensor(type, index);
			if (sensor != NULL)
			{
				DEBUG_MSG("SerialReceiver::Update:SetValue: (" << type << ", " << index << ", " << value << ") " << message.Get());
				sensor->SetValue(value);
			}
		}
		catch (const std::exception& e)
		{
			DEBUG_MSG("SerialReceiver::Update:Exception: " << e.what());
		}
	}
}
