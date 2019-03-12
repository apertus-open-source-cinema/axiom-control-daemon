#ifndef MEMORYADAPTER_H
#define MEMORYADAPTER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <sys/syslog.h>
#include <unistd.h>

#include "IAdapter.h"

#include "../Helpers/Helpers.h"

//#include "../Log/DefaultLogger.h"

class MemoryAdapter : public IAdapter
{
protected:
    uintptr_t baseAddress;

public:
    void ReadDescriptions(std::string descriptionFile) override
    {
        UNUSED(descriptionFile);
    }

    void CheckDevices()  override {}

    void ReadByte(uint8_t data)  override
    {
        UNUSED(data);
    }
    void WriteByte(uint8_t data)  override
    {
        UNUSED(data);
    }

    virtual void WriteWord(unsigned reg, uint16_t val)
    {
        volatile uint32_t* ptr = reinterpret_cast<uint32_t*>(baseAddress);
        ptr[reg] &= ~val;
        ptr[reg] |= val;
    }

    virtual uint16_t ReadWord(unsigned reg)
    {
        volatile uint32_t* ptr = reinterpret_cast<uint32_t*>(baseAddress);
        return ptr[reg];
    }

    
    void ReadBlock(uint8_t *data, unsigned int length) override
    {
        UNUSED(data);
        UNUSED(length);
    }

    void WriteBlock(uint8_t *data, unsigned int length) override
    {
        UNUSED(data);
        UNUSED(length);
    }

    virtual void* MemoryMap(uintptr_t address, uint32_t size)
    {
        baseAddress = address;

        std::string message = "";

        // TODO: Check if alignment is required
        int fd = open("/dev/mem", O_RDWR | O_SYNC);
        if (fd == -1)
        {
            message = "Error (open /dev/mem): " + std::string(strerror(errno));
            // TODO: Rework logging
            //DefaultLogger::Log(message);
            return reinterpret_cast<void*>(-1);
        }

        void* result = nullptr;
        
        result = mmap(reinterpret_cast<void*>(address), size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, address);
        if(result == reinterpret_cast<void*>(-1))
        {
            // TODO: Add error log
            message = "Cannot map memory to address: " + std::to_string(address);
            // TODO: Rework logging
            //DefaultLogger::Log(message);
        }

        baseAddress = reinterpret_cast<uintptr_t>(result);

        return result;
    }

    virtual int MemoryUnmap(uint32_t address, uint32_t size)
    {
        return munmap(reinterpret_cast<void*>(address), size);
    }

    virtual void Execute() override
    {

    }

    std::vector<std::string> GetAvailableMethods()
    {
        std::vector<std::string> availableMethods;
        availableMethods.push_back("Test1");
        availableMethods.push_back("Test2");

        return availableMethods;
    }
};

#endif // MEMORYADAPTER_H
