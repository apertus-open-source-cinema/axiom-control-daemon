#include "WSServer.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

WSServer::WSServer(uint16_t port):
    _messageHandler(std::make_shared<MessageHandler>())
{
    _port = port;

    Setup();
}

WSServer::~WSServer()
{    
}

void WSServer::Setup()
{
    _server = std::make_shared<wsserver>();

    auto messageHandler = [&](wsserver* s, websocketpp::connection_hdl hdl, wsserver::message_ptr msg)
    {
        //ws->send("ACK", 3, opCode);
        std::string convertedMessage = msg->get_payload();
        std::string responseMessage;
        bool status = _messageHandler->ProcessMessage(convertedMessage, responseMessage);
        
        s->send(hdl, responseMessage, msg->get_opcode());
    };

    _server->set_access_channels(websocketpp::log::alevel::all);
    _server->clear_access_channels(websocketpp::log::alevel::frame_payload);

    // Initialize Asio
    _server->init_asio();

    // Register our message handler
    _server->set_message_handler(std::bind(messageHandler, _server.get(), ::_1, ::_2));
}

void WSServer::Start()
{    
    _server->listen(_port);
    _server->start_accept();
    _server->run();
}
