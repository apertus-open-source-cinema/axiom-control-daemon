#include <iostream>

#include "../API_WS/MessageHandler.h"

void HandleCommandLine(const int& argc, char* argv[], std::string& secondValue)
{
    if(argc != 5)
    {
        std::cout << "Not enough arguments. Example: ./DaemonCLI image_sensor set analog_gain 2" << std::endl;
        exit(1);
    }

    if( argc == 6)
    {
        secondValue = argv[5];
    }
}

int main(int argc, char *argv[])
{
    std::string secondValue = "";
    HandleCommandLine(argc, argv, secondValue);

    MessageHandler messageHandler;
    messageHandler.AddDaemonRequest("DaemonCLI", argv[1], argv[2], argv[3], argv[4], secondValue);
    std::unique_ptr<DaemonRequestT> req;
    messageHandler.TransferData(req);
    
    // TODO (balysche): Show reply using req

    return 0;
}
