#include "CMV12000Adapter.h"

#include "MemoryAdapterDummy.h"

#ifdef ENABLE_MOCK
using MemAdapter = MemoryAdapterDummy;
#else
using MemAdapter = MemoryAdapter;
#endif

#define GETTER_FUNC(A) std::bind(A, this, std::placeholders::_1, std::placeholders::_2)
#define SETTER_FUNC(A) std::bind(A, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

CMV12000Adapter::CMV12000Adapter() :
    address(0x60000000),
    memorySize(0x00020000),
    _memoryAdapter(std::make_shared<MemAdapter>())
{
    // Map the regions at start, to prevent repeating calls of mmap()
    _memoryAdapter->MemoryMap(address, memorySize);

    RegisterAvailableMethods();
}

void CMV12000Adapter::RegisterAvailableMethods()
{
    //RegisterMethods("set_gain", std::bind(&CMV12000Adapter::SetGain, this, std::placeholders::_1));

    // TODO: Add macros to simplify registering of getter and setter, e.g. GETTER_FUNC(CMV12000Adapter, GetGain)
    AddParameterHandler("analog_gain", GETTER_FUNC(&CMV12000Adapter::GetAnalogGain), SETTER_FUNC(&CMV12000Adapter::SetAnalogGain));
    AddParameterHandler("digital_gain", GETTER_FUNC(&CMV12000Adapter::GetDigitalGain), SETTER_FUNC(&CMV12000Adapter::SetDigitalGain));
}

CMV12000Adapter::~CMV12000Adapter()
{
    _memoryAdapter->MemoryUnmap(address, memorySize);
}

bool CMV12000Adapter::SetAnalogGain(std::string gainValue, std::string, std::string& message)
{
    if(gainValue.length() > 1)
    {
        message = "SetGain() | Gain out of range 0 -> 4";
        return false;
    }

    _analogGainValue = static_cast<unsigned int>(stoi(gainValue));
    if(_analogGainValue > 7)
    {
        // TODO: Log error for unsuitable parameter
        message = "SetAnalogGain() | Gain index out of range 0 -> 7";
        return false;
    }

    // Set division first, to prevent overwriting gain values
    SetConfigRegister(115, _divPGA[_analogGainValue]);
    SetConfigRegister(115, _gainPGA[_analogGainValue]);
    //    SetConfigRegister(100, 1);
    //    SetConfigRegister(87, 2000);
    //    SetConfigRegister(88, 2000);

    return true;
}

bool CMV12000Adapter::GetAnalogGain(std::string& gainValue, std::string& message)
{
    UNUSED(message);

    gainValue = std::to_string(_analogGainValue);
    return true;
}

bool CMV12000Adapter::SetDigitalGain(std::string gainValue, std::string, std::string &message)
{
    _digitalGainValue = static_cast<unsigned int>(stoi(gainValue));
    // TODO: Add handling of 3/3 gain value
    if(_digitalGainValue > 9)
    {
        // TODO: Log error for unsuitable parameter
        message = "SetDigitalgGain() | Gain index out of range 0 -> 9";
        return false;
    }

    SetConfigRegister(117, _digitalGainValues[_digitalGainValue]);

    return true;
}

bool CMV12000Adapter::GetDigitalGain(std::string &gainValue, std::string &message)
{
    UNUSED(message);

    gainValue = std::to_string(_digitalGainValue);
    return true;
}

void CMV12000Adapter::SetConfigRegister(u_int8_t registerIndex, unsigned int value)
{
    std::string message = "SetConfigRegister() - Register: " + std::to_string(registerIndex) + " | Value: " + std::to_string(value);
    JournalLogger::Log(message);

    _memoryAdapter->WriteWord(registerIndex, value);
}

void CMV12000Adapter::Execute()
{
    // TODO: Iterate through all added settings and apply them to SPI registers
}

//std::string CMV12000Adapter::GetParameter(std::string parameterName)
//{
//    std::unordered_map<std::string, ParameterHandler>::const_iterator got = parameterHandlers.find (parameterName);
//    if ( got == parameterHandlers.end() )
//    {
//        JournalLogger::Log("ImageSensor: Handler not found");
//        return false;
//    }
//    else
//    {
//        JournalLogger::Log("ImageSensor: Handler found");

//        auto handler = got->second;
//        return handler.Getter(*this);
//    }
//}
