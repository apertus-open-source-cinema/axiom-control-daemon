#ifndef WSSERVER_H
#define WSSERVER_H

#include <iostream>

#define ASIO_STANDALONE
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "MessageHandler.h"

struct JSONSetting;

class WSServer
{
    typedef websocketpp::server<websocketpp::config::asio> wsserver;

    std::shared_ptr<wsserver> _server;
    uint16_t                  _port;

    std::shared_ptr<IMessageHandler> _messageHandler;

public:
    explicit WSServer(uint16_t port);
    ~WSServer();

    void Start();

protected:
    void Setup();
};

#endif // WSSERVER_H
