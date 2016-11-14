#include <json-develop/src/json.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>

#include <iostream>

#include <DeviceSetup.hxx>
#include <DummySensor.hxx>
#include <HostFileReader.hxx>

typedef websocketpp::client<websocketpp::config::asio> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef client::message_ptr message_ptr;
using json = nlohmann::json;

void on_open(client* s, websocketpp::connection_hdl hdl)
{
	std::cout << "CONNECTED to server" << std::endl;
}

void on_close(client* s, websocketpp::connection_hdl hdl) 
{
	std::cout << "DISCONNECTED from server" << std::endl;
}

DeviceSetup setup(
	"CLIENT0001",
	DevCapabilities_3g | DevCapabilities_bluetooth30 | DevCapabilities_ethernet100m,
	{
		new DummySensor(SensorTypeTemperature, SensorUnitDegreesCelsius, SensorPlacementInside, 1, -100.0, 200.0, Position{ 3.0, 10.0, -10.6 }),
		new DummySensor(SensorTypeTemperature, SensorUnitDegreesCelsius, SensorPlacementInside, 1, -100.0, 200.0, Position{ 4.0, 10.0, -10.5 }),
		new DummySensor(SensorTypeTemperature, SensorUnitDegreesCelsius, SensorPlacementOutside, 1, -100.0, 200.0, Position{ 5.0, 10.0, -10.4 }),
		new DummySensor(SensorTypeHumidity, SensorUnitPercent, SensorPlacementInside, 1, -100.0, 200.0, Position{ 6.0, 10.0, -10.3 }),
		new DummySensor(SensorTypeHumidity, SensorUnitPercent, SensorPlacementOutside, 1, -100.0, 200.0, Position{ 7.0, 10.0, -10.2 }),
		new DummySensor(SensorTypeSound, SensorUnitDecibel, SensorPlacementInside, 1, -100.0, 200.0, Position{ 8.0, 10.0, -10.1 }),
		new DummySensor(SensorTypeSound, SensorUnitDecibel, SensorPlacementOutside, 1, -100.0, 200.0, Position{ 9.0, 10.0, -10.0 })
	});

// Define a callback to handle incoming messages
void on_message(client* s, websocketpp::connection_hdl hdl, message_ptr msg) 
{
	std::cout << "Received a message from the server: \"" << msg->get_payload() << "\"" << std::endl;

	json j = json::parse(msg->get_payload().c_str());

	auto device_setup = j.find("GetDeviceSetup");
	if (device_setup != j.end()) 
	{	
		std::cout << "GetDeviceSetup found" << std::endl;

		setup.ParseRequestJson(device_setup->dump());

		std::cout << "GetDeviceSetup parsed" << std::endl;

		std::string response(setup.GetResponseJson());

		std::cout << "GetDeviceSetup response" << std::endl;

		try 
		{
			s->send(hdl, response.c_str(), response.length() + 1, websocketpp::frame::opcode::TEXT);
			std::cout << "Send websocket message succesfully: \"" << response << "\"" << std::endl;
		}
		catch (const websocketpp::lib::error_code& e) 
		{
			std::cout << "WebSocket response failed because: " << e
				<< "(" << e.message() << ")" << std::endl;
		}
	}
}

int main() 
{
	HostFileReader host;

	std::string response(setup.GetRequestJson());

	// Create a server endpoint
	client echo_client;

	try 
	{
		// Set logging settings
		echo_client.set_access_channels(websocketpp::log::alevel::all);
		echo_client.clear_access_channels(websocketpp::log::alevel::frame_payload);

		// Initialize Asio
		echo_client.init_asio();

		// Register our message handler
		echo_client.set_message_handler(bind(&on_message, &echo_client, ::_1, ::_2));

		echo_client.set_open_handler(bind(&on_open, &echo_client, ::_1));
		echo_client.set_close_handler(bind(&on_close, &echo_client, ::_1));

		websocketpp::lib::error_code ec;

		client::connection_ptr con = echo_client.get_connection(host.GetHost(), ec);
		if (ec) 
		{
			std::cout << "could not create connection to \"" << host.GetHost() << "\" because: " << ec.message() << std::endl;
			return 0;
		}

		echo_client.connect(con);

		// Start the ASIO io_service run loop
		echo_client.run();
	}
	catch (websocketpp::exception const & e) 
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception const & e)
	{
		std::cout << "unknown exception occurred: " << e.what() << std::endl;
	}

	std::cout << "Press return key to exit...";
	std::string s;
	getline(std::cin, s);
	return 0;
}
