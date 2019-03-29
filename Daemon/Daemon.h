#ifndef DAEMON_H
#define DAEMON_H

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unordered_map>

#include "json/json.hpp"
using json = nlohmann::json;

#include "../Adapter/CMV12000Adapter.h"
#include "../Adapter/I2CAdapter.h"
#include "../Adapter/MemoryAdapter.h"

#include <Schema/axiom_daemon_generated.h>

class ILogger;

class Daemon
{
    std::shared_ptr<ILogger> _logger;

    std::string _socketPath;

    // Used for logging
    std::string _processID;

    bool _running;

    // TODO: Allow multiple connections
    int         _socketDesc;
    sockaddr_un _name;

    std::string _statusMessage;

    // IAdapter* _memoryAdapter = nullptr;
    // IAdapter* _i2cAdapter = nullptr;

    json availableParameters;

    flatbuffers::FlatBufferBuilder _builder;

    std::unordered_map<std::string, std::shared_ptr<IDaemonModule>>           _modules;
    std::unordered_map<std::string, std::shared_ptr<IDaemonModule>>::iterator _module_iterator;

    // TODO: Move processing to a thread, so it doesn't block main thread in the future
    void Process();

    void SetupSocket();

    ssize_t RetrieveIncomingData(int socket, uint8_t* receivedBuffer, unsigned int bufferSize);

    void ProcessReceivedData(uint8_t* receivedBuffer);

    bool ProcessGeneralRequest(std::unique_ptr<DaemonRequestT>& req);

    void ProcessClient(int socket);

    void ProcessAvailableParameters(std::function<void(IDaemonModule*, json&)>);
    void RetrieveCurrentParameterValues(IDaemonModule* module, json& description);
    void ResetParameterValues(IDaemonModule* module, json& description);

public:
    Daemon();

    ~Daemon();

    void Setup();
    void Start();
};

#endif // DAEMON_H
