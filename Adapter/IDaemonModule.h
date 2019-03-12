#ifndef IDAEMONMODULE_H
#define IDAEMONMODULE_H

#include <functional>
#include <vector>
#include <string>
#include <unordered_map>

#include "../Log/Logger.h"

class IDaemonModule
{
    // string& value, string& message, returns: bool - success or fail
    using GetterFunc = std::function<bool(std::string&, std::string&)>;
    // string value1, string value2, string& message, returns: bool - success or fail
    using SetterFunc = std::function<bool(std::string, std::string, std::string&)>;

    struct ParameterHandler
    {
        GetterFunc Getter;
        SetterFunc Setter;
    };

    std::unordered_map<std::string, ParameterHandler> parameterHandlers;

    // TODO: Don't remove commented and related parts yet, maybe we need individual methods later, to trigger special functionality, which ar not related to parameters directly
    //typedef std::function<bool(std::string&)> CallbackFunc;

    //std::unordered_map<std::string, CallbackFunc> _registeredMethods;
    //std::unordered_map<std::string, CallbackFunc>::const_iterator it;

    //void RegisterMethods(std::string name, CallbackFunc func)
    //{
    //    _registeredMethods.emplace(std::make_pair(name, func));
    //}

    //std::vector<std::string> GetRegisteredMethodNames()
    //{
    //    std::vector<std::string> keys;
    //
    //    for(auto kv : _registeredMethods)
    //    {
    //        keys.push_back(kv.first);
    //    }
    //
    //    return keys;
    //}

    //bool ProcessMethod(std::string methodName, std::string value)
    //{
    //    it = _registeredMethods.find(methodName);
    //
    //    if(it != _registeredMethods.end())
    //    {
    //        return it->second(value);
    //    }
    //}


    //std::vector<std::string> GetAvailableMethods()
    //{
    //    return GetRegisteredMethodNames();
    //}

protected:
    virtual void RegisterAvailableMethods() = 0;

    void AddParameterHandler(std::string name, GetterFunc getter, SetterFunc setter)
    {
        parameterHandlers.insert(std::make_pair(name, ParameterHandler{getter, setter}));
    }

public:
    virtual ~IDaemonModule() = default;

    //virtual std::vector<std::string>GetAvailableMethods() = 0;

    bool HandleParameter(std::string command, std::string parameterName, std::string& parameterValue1, std::string& parameterValue2, std::string& message)
    {
        std::string originalParameterName = parameterName;
        std::unordered_map<std::string, ParameterHandler>::const_iterator got = parameterHandlers.find (parameterName);
        if ( got == parameterHandlers.end() )
        {
            DAEMON_LOG_ERROR("Handler not found");
            message = "Handler not found: " + parameterName;
            return false;
        }
        else
        {
            DAEMON_LOG_INFO("Handler found");

            auto handler = got->second;
            //auto method = (command == "set") ? handler.Setter : handler.Getter;
            bool result = false;
            if(command == "set")
            {
                result = handler.Setter(parameterValue1, parameterValue2, message);
            }
            else if(command == "get")
            {
                result = handler.Getter(parameterValue1, message);
            }

            return result;
        }
    }
};

#endif //IDAEMONMODULE_H
