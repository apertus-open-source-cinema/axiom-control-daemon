#ifndef MEMORYADAPTERDUMMY_H
#define MEMORYADAPTERDUMMY_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <sys/syslog.h>
#include <unistd.h>

#include "MemoryAdapter.h"

#include "../Helpers/Helpers.h"

// For development on PC, which prevents crashes when trying to set values in RAM directly
class MemoryAdapterDummy : public MemoryAdapter
{
public:
    void ReadDescriptions(std::string descriptionFile) override
    {
        UNUSED(descriptionFile);
    }

    void CheckDevices() override {}

    void ReadByte(uint8_t data) override
    {
        UNUSED(data);
    }
    void WriteByte(uint8_t data) override
    {
        UNUSED(data);
    }

    void WriteWord(unsigned reg, uint16_t val) override
    {
        UNUSED(reg);
        UNUSED(val);
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

    void* MemoryMap(uintptr_t address, uint32_t size) override
    {
        UNUSED(address);
        UNUSED(size);

        return nullptr;
    }

    int MemoryUnmap(uint32_t address, uint32_t size) override
    {
        UNUSED(address);
        UNUSED(size);

        return 0;
    }

    virtual void Execute() override
    {

    }
};

#endif // MEMORYADAPTERDUMMY_H
