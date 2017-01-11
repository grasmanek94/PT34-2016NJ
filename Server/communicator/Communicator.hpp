#pragma once
#include <set>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>

#include "HostFileReader.hpp"
#include <SharedMemoryQueue.hpp>

typedef websocketpp::client<websocketpp::config::asio> client;
typedef client::message_ptr message_ptr;

class Communicator
{
private:

	HostFileReader host;
	SharedMemoryQueue in_queue;
	SharedMemoryQueue out_queue;
	client websocket_client;

	void on_open(websocketpp::connection_hdl hdl);
	void on_close(websocketpp::connection_hdl hdl);
	void on_message(websocketpp::connection_hdl hdl, message_ptr msg);
	void on_fail(websocketpp::connection_hdl hdl);

	typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> con_list;
	con_list connections;

	void Reconnect();
public:
	Communicator();
	~Communicator();
	void Run();
};