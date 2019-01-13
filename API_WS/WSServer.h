#ifndef WSSERVER_H
#define WSSERVER_H

#include <iostream>

#define ASIO_STANDALONE
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

//#include <App.h>
#include "MessageHandler.h"

struct JSONSetting;
//namespace uWS
//{
//    struct TemplatedApp;
//    typedef TemplatedApp App;
//}

class WSServer
{
    typedef websocketpp::server<websocketpp::config::asio> wsserver;

    std::shared_ptr<wsserver> _server;
    uint16_t _port;

    std::shared_ptr<IMessageHandler> _messageHandler;

public:
    explicit WSServer(int port);
    ~WSServer();

    void Start();

protected:
    void Setup();
};

#endif //WSSERVER_H
