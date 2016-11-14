#include <set>
#include <thread>
#include <iostream>

#include <json-develop/src/json.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>

#include <DeviceSetup.hxx>

using json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

std::set<websocketpp::connection_hdl::element_type*> clients;

void on_open(server* s, websocketpp::connection_hdl hdl)
{
	clients.insert(hdl.lock().get());
	/*std::cout << "on_open called with hdl: " << hdl.lock().get()
		<< std::endl;*/

	DeviceSetup setup;
	std::string request(setup.GetRequestJson());

	try {
		s->send(hdl, request.c_str(), request.length() + 1, websocketpp::frame::opcode::TEXT);
	}
	catch (const websocketpp::lib::error_code& e) {
		std::cout << "Echo failed because: " << e
			<< "(" << e.message() << ")" << std::endl;
	}
}

void on_close(server* s, websocketpp::connection_hdl hdl)
{
	clients.erase(hdl.lock().get());
	/*std::cout << "on_close called with hdl: " << hdl.lock().get()
		<< std::endl;*/
}

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg)
{
	std::cout << "----------------" << std::endl << json::parse(msg->get_payload().c_str()) << std::endl << "----------------" << std::endl;
	/*std::cout << "on_message called with hdl: " << hdl.lock().get()
		<< " and message: " << msg->get_payload()
		<< std::endl;

	// check for a special command to instruct the server to stop listening so
	// it can be cleanly exited.
	if (msg->get_payload() == "stop-listening") {
		s->stop_listening();
		return;
	}

	try {
		s->send(hdl, msg->get_payload(), msg->get_opcode());
	}
	catch (const websocketpp::lib::error_code& e) {
		std::cout << "Echo failed because: " << e
			<< "(" << e.message() << ")" << std::endl;
	}*/
}

int main() {
	// Create a server endpoint
	server echo_server;

	try
	{
		// Set logging settings
		echo_server.set_access_channels(websocketpp::log::alevel::all);
		echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

		// Initialize Asio
		echo_server.init_asio();

		// Register our message handler
		echo_server.set_message_handler(bind(&on_message, &echo_server, ::_1, ::_2));

		echo_server.set_open_handler(bind(&on_open, &echo_server, ::_1));
		echo_server.set_close_handler(bind(&on_close, &echo_server, ::_1));

		// Listen on port 9002
		echo_server.listen(9002);

		// Start the server accept loop
		echo_server.start_accept();

		// Start the ASIO io_service run loop
		while (true)
		{
			echo_server.poll();

			// you can do some processing here if needed

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
	catch (websocketpp::exception const & e) 
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception const & e) 
	{
		std::cout << "other exception: " << e.what() << std::endl;
	}
}