#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "IMessageHandler.h"
#include "MessageDefines.h"

#include <sys/socket.h>
#include <sys/un.h>

#include <Schema/axiom_daemon_generated.h>

namespace ns
{
    struct JSONSetting;
}

class MessageHandler : public IMessageHandler
{
    std::string        socketPath;
    int                clientSocket;
    struct sockaddr_un address;
    socklen_t          _sockaddrLength;

    // TODO (BAndiT1983): Rework, possibly shrink it, as the data is much smaller currently
    char _response[1024];

    // Using separate lists for now as it seems that flatbuffers does not use inheritance for unions
    std::vector<flatbuffers::Offset<DaemonRequest>> _settings;

    // std::vector<const ImageSensorSetting*> _settingsIS;

    flatbuffers::FlatBufferBuilder* _builder = nullptr;

public:
    MessageHandler();
    ~MessageHandler() override;

    // Process JSON message and return response
    virtual bool ProcessMessage(std::string message, std::string& response) override;

    void SetupSocket();

    void Execute();
    void TransferData(std::unique_ptr<DaemonRequestT>& req);

    void AddDaemonRequest(const std::string& sender, const std::string& module,
                          const std::string& command, const std::string& parameter,
                          const std::string& value1, const std::string& value2 = nullptr);

    void OutputReceivedData(ns::JSONSetting setting, std::string& message);
};

#endif // MESSAGEHANDLER_H
