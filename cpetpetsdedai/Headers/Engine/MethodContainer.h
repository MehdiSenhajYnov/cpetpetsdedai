#pragma once
#include <functional>
#include <map>
#include <string>

class MethodContainer
{
public:

    template <typename Class,typename ReturnType, typename... Args>
    static void AddFunction(std::string name, ReturnType(Class::*function)(Args... args), Class* instance)
    {
        std::function<ReturnType(Args...)> lambda = [function, instance](Args... args) {
            (instance->*function)(args...);
        };
        GetFunctionsWith<ReturnType, Args...>()[name] = lambda;
    }
    
    template <typename ReturnType, typename... Args>
    static std::map<std::string, std::function<ReturnType(Args...)>>& GetFunctionsWith()
    {
        static std::map<std::string, std::function<ReturnType(Args...)>> allfunctions;
        return allfunctions;
    }

};
