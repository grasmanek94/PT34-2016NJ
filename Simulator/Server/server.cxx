#include <set>
#include <thread>
#include <iostream>

#include <json-develop/src/json.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef server::message_ptr message_ptr;
std::set<websocketpp::connection_hdl::element_type*> clients;

void on_close(server* s, websocketpp::connection_hdl hdl)
{
	clients.erase(hdl.lock().get());
}

void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg)
{
	std::cout 
		<< "----------------" << std::endl 
		<< nlohmann::json::parse(msg->get_payload().c_str()) 
		<< std::endl << "----------------" << std::endl;
}

void on_open(server* s, websocketpp::connection_hdl hdl)
{
	clients.insert(hdl.lock().get());

	std::string request("{\"GetDeviceSetup\":null}");

	try {
		s->send(hdl, request.c_str(), request.length() + 1, websocketpp::frame::opcode::TEXT);
	}
	catch (const websocketpp::lib::error_code& e) {
		std::cout << "Echo failed because: " << e
			<< "(" << e.message() << ")" << std::endl;
	}
}

int main() 
{
	server echo_server;

	try
	{
		echo_server.set_access_channels(websocketpp::log::alevel::all);
		echo_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

		echo_server.init_asio();

		echo_server.set_message_handler(bind(&on_message, &echo_server, ::_1, ::_2));

		echo_server.set_open_handler(bind(&on_open, &echo_server, ::_1));
		echo_server.set_close_handler(bind(&on_close, &echo_server, ::_1));

		echo_server.listen(9002);
		echo_server.start_accept();

		while (true)
		{
			echo_server.poll();

			// you can do some processing here if needed
			// eg loop all clients and send a ping to them

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}
	}
	catch (websocketpp::exception const & e) 
	{
		std::cout << "WebSocket exception occured: " << e.what() << std::endl;
	}
	catch (std::exception const & e) 
	{
		std::cout << "unknown exception occurred: " << e.what() << std::endl;
	}
}