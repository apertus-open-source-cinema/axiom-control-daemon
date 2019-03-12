#include <memory>

#include "Daemon.h"

int main(int argc, char *argv[])
{    
    UNUSED(argc);
    UNUSED(argv);

    const std::unique_ptr<Daemon> daemon(new Daemon());
    daemon->Setup();
    daemon->Start();

    return 0;
}
