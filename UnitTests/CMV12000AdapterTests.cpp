#include <catch/catch.hpp>

#include "../Adapter/CMV12000Adapter.h"

// When enabled, then modified class is used to prevent crashes on PC (as RAM access is different from ARM)
#ifdef ENABLE_MOCK
    class CMV12000AdapterMod : public CMV12000Adapter
    {
    public:
        virtual void SetConfigRegister(u_int8_t registerIndex, unsigned int value) override
        {
        // TODO: Add implementation
        //std::string message = "SetConfigRegister() - Register: " + std::to_string(registerIndex) + " | Value: " + std::to_string(value);
        //JournalLogger::Log(message);
        //_memoryAdapter->WriteWord(registerIndex, value);
        }
    };

    using CMV12000AdapterClass = CMV12000AdapterMod;    
#else    
    using CMV12000AdapterClass = CMV12000Adapter;
#endif

TEST_CASE( "Gain setting", "[CMV12000Adapter]" ) 
{
    CMV12000AdapterClass adapter;
    std::string message = "";
    std::string parameterValue = "3";
    CHECK( adapter.HandleParameter("set_gain", parameterValue, message) == true );
    REQUIRE( adapter.HandleParameter("get_gain", parameterValue, message) == true );
}

TEST_CASE( "Dummy parameter test, test should succeed if SetParameter() returns false (no handler found)", "[CMV12000Adapter]" ) 
{
    CMV12000AdapterClass adapter;
    std::string message = "";
    std::string parameterValue = "3";
    REQUIRE( adapter.HandleParameter("dummyParameter", parameterValue, message) == false );
}