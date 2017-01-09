#include <stdexcept>

#include <Debug.hpp>
#include "Communicator.hpp"
#include "RawQueue.hpp"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

volatile sig_atomic_t done = 0;

void term(int signum)
{
	DEBUG_MSG("TERMINATION REQUESTED");
	done = 1;
}

void Communicator::on_open(websocketpp::connection_hdl hdl)
{
	DEBUG_MSG("Communicator::on_open");
	connections.insert(hdl);

	// because for now only 1 outgoing connection at once
	in_queue.Clear();
	out_queue.Clear();

	// make the other process send the DeviceInfo after connecting, nice uh?
	SharedMemoryQueueMessage message(std::string("{\"GetDeviceSetup\":null}"));
	if (in_queue.Push(&message))
	{
		DEBUG_MSG("Pushed SUCCESS: " << message.Get());
	}
	else
	{
		DEBUG_MSG("Pushed FAILURE: " << message.Get());
	}
}

void Communicator::on_close(websocketpp::connection_hdl hdl)
{
	DEBUG_MSG("Communicator::on_close");
	connections.erase(hdl);
	Reconnect();
}

void Communicator::on_message(websocketpp::connection_hdl hdl, message_ptr msg)
{
	std::string payload(msg->get_payload());
	DEBUG_MSG("Communicator::on_message: " << payload);
	if (payload.size() >= max_items_for_RawQueue)
	{
		websocket_client.send(hdl, "\
		{\
			\"errors\": [\
				{\
					\"status\": \"-2\",\
						\"title\" : \"Message too long\",\
						\"detail\" : \"The message exceeds the maximum size of " + std::to_string(max_items_for_RawQueue-1) + " characters.\"\
				}\
			]\
		}", websocketpp::frame::opcode::text);
		return;
	}

	SharedMemoryQueueMessage message(payload);
	if (!in_queue.Push(&message))
	{
		websocket_client.send(hdl, "\
		{\
			\"errors\": [\
				{\
					\"status\": \"-1\",\
						\"title\" : \"Out of memory\",\
						\"detail\" : \"Message queue is full.\"\
				}\
			]\
		}", websocketpp::frame::opcode::text);
		return;
	}

	DEBUG_MSG("Communicator::pushed_message: " << message.Get());
}

Communicator::Communicator()
 : in_queue("in_webscktmsg"), out_queue("out_webscktmsg")
{
	DEBUG_MSG("Communicator::Communicator");
	// Set logging settings
#ifdef _DEBUG
	websocket_client.set_access_channels(websocketpp::log::alevel::all);
	websocket_client.clear_access_channels(websocketpp::log::alevel::frame_payload);
#else
	websocket_client.set_access_channels(websocketpp::log::alevel::none);
	websocket_client.clear_access_channels(websocketpp::log::alevel::none);
#endif

	// Initialize Asio
	websocket_client.init_asio();

	// Register our message handler
	websocket_client.set_message_handler(bind(&Communicator::on_message, this, ::_1, ::_2));

	websocket_client.set_open_handler(bind(&Communicator::on_open, this, ::_1));
	websocket_client.set_close_handler(bind(&Communicator::on_close, this, ::_1));

}

Communicator::~Communicator()
{
	DEBUG_MSG("Communicator::~Communicator");
}

void Communicator::Reconnect()
{
	DEBUG_MSG("Communicator::Reconnect");
	websocketpp::lib::error_code ec;

	client::connection_ptr con = websocket_client.get_connection(host.GetHost(), ec);
	if (ec)
	{
		throw std::runtime_error(("could not create connection to \"" + host.GetHost() + "\" because: " + ec.message()).c_str());
	}

	websocket_client.connect(con);
}

void Communicator::Run()
{
	DEBUG_MSG("Communicator::Run");

	static bool terminator_initialized = false;
	if (!terminator_initialized)
	{
		DEBUG_MSG("Communicator::terminator_initialized");
		terminator_initialized = true;
		struct sigaction action;
		memset(&action, 0, sizeof(struct sigaction));
		action.sa_handler = term;
		sigaction(SIGTERM, &action, NULL);
	}

	Reconnect();

	SharedMemoryQueueMessage message;

	DEBUG_MSG("Communicator::loop");
	while (!done)
	{
		websocket_client.poll();

		// send out_queue to belgie
		if (out_queue.TryPop(&message))
		{
			std::string s_message(message.Get());
			DEBUG_MSG("Communicator::popped_message: " << s_message);
			for (auto it : connections) 
			{
				websocket_client.send(it, s_message, websocketpp::frame::opcode::text);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}