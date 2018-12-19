#include <catch/catch.hpp>

#include "../Adapter/CMV12000Adapter.h"

TEST_CASE( "Analog gain setting", "[CMV12000Adapter]" )
{
    CMV12000Adapter adapter;
    std::string message = "";
    std::string parameterValue = "3";
    CHECK( adapter.HandleParameter("set", "analog_gain", parameterValue, message) == true );
    REQUIRE( adapter.HandleParameter("get", "analog_gain", parameterValue, message) == true );
}

TEST_CASE( "Digital gain setting", "[CMV12000Adapter]" )
{
    CMV12000Adapter adapter;
    std::string message = "";
    std::string parameterValue = "3";
    CHECK( adapter.HandleParameter("set", "digital_gain", parameterValue, message) == true );
    REQUIRE( adapter.HandleParameter("get", "digital_gain", parameterValue, message) == true );
}

TEST_CASE( "Dummy parameter test, test should succeed if SetParameter() returns false (no handler found)", "[CMV12000Adapter]" ) 
{
    CMV12000Adapter adapter;
    std::string message = "";
    std::string parameterValue = "3";
    REQUIRE( adapter.HandleParameter("get", "dummyParameter", parameterValue, message) == false );
}

TEST_CASE( "Test available methods retrieval", "[DaemonModule]" )
{
    CMV12000Adapter adapter;

    std::vector<std::string> availableMethods;// = adapter.GetAvailableMethods();

    //REQUIRE(availableMethods.size() == 3);
    //REQUIRE( responseMessage == expectedData );
}
