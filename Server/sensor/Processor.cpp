#include <csignal>
#include <thread>
#include <json/json.hpp>
#include "Processor.hpp"
#include "SimpleSensor.hpp"
#include "SensorData.hpp"
#include <Timer.hpp>

using namespace nlohmann;
volatile sig_atomic_t done = 0;

void term(int signum)
{
	done = 1;
}

Processor::Processor()
	: in_queue("in_webscktmsg"), out_queue("out_webscktmsg"),
	device(
		DevCapabilities_3g | DevCapabilities_bluetooth30 | DevCapabilities_ethernet100m,
		{
			new SimpleSensor(SensorTypeTemperature, SensorUnitDegreesCelsius, SensorPlacementInside, 1, -100.0, 200.0, Position{ 3.0, 10.0, -10.6 }),
			new SimpleSensor(SensorTypeTemperature, SensorUnitDegreesCelsius, SensorPlacementInside, 1, -100.0, 200.0, Position{ 4.0, 10.0, -10.5 }),
			new SimpleSensor(SensorTypeTemperature, SensorUnitDegreesCelsius, SensorPlacementOutside, 1, -100.0, 200.0, Position{ 5.0, 10.0, -10.4 }),
			new SimpleSensor(SensorTypeHumidity, SensorUnitPercent, SensorPlacementInside, 1, -100.0, 200.0, Position{ 6.0, 10.0, -10.3 }),
			new SimpleSensor(SensorTypeHumidity, SensorUnitPercent, SensorPlacementOutside, 1, -100.0, 200.0, Position{ 7.0, 10.0, -10.2 }),
			new SimpleSensor(SensorTypeSound, SensorUnitDecibel, SensorPlacementInside, 1, -100.0, 200.0, Position{ 8.0, 10.0, -10.1 }),
			new SimpleSensor(SensorTypeSound, SensorUnitDecibel, SensorPlacementOutside, 1, -100.0, 200.0, Position{ 9.0, 10.0, -10.0 })
		})
{
	static bool terminator_initialized = false;
	if (!terminator_initialized)
	{
		terminator_initialized = true;
		struct sigaction action;
		memset(&action, 0, sizeof(struct sigaction));
		action.sa_handler = term;
		sigaction(SIGTERM, &action, NULL);
	}
}

Processor::~Processor()
{

}

void Processor::Run()
{
	SharedMemoryQueueMessage message;
	Timer data_send_timer;

	data_send_timer.Start();

	while (!done)
	{
		// recv from belgie
		if (in_queue.TryPop(&message))
		{
			json j = json::parse(message.Get().c_str());

			auto device_setup = j.find("GetDeviceSetup");
			if (device_setup != j.end())
			{
				// send to belgie
				message.Set(device.GetResponseJson());
				out_queue.Push(&message);
			}
		}

		if (data_send_timer.ElapsedMilliseconds() > 10000)
		{
			data_send_timer.Restart();

			SensorData data(&device);
			data.ParseRequestJson("{}");

			// send to belgie
			message.Set(data.GetResponseJson());
			out_queue.Push(&message);
		}

		// update values from serial / arduino here
		{
			// todo
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}
