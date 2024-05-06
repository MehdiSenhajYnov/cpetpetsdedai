#pragma once
#include <sstream>
#include <string>

class BaseField {
public:
    BaseField() = default;
    BaseField(const std::string& _name) : name(_name) {}
    std::string name;
    virtual ~BaseField() {}

    virtual std::string GetValueAsString() = 0;

};


template <CanString T>
class Field : public BaseField
{
public:
    Field() {}
    Field(const std::string& _name) : BaseField(_name) {}
    Field(const std::string& _name, std::function<T()> _getValue, std::function<void(T)> _setValue) : BaseField(_name), GetValue(_getValue), SetValue(_setValue) {}
    ~Field() override {}

    //constexpr 
    
    std::string GetValueAsString() override
    {
        return getAsString(GetValue());
    }

    template <CanString U>
    static std::string PrintString(U value)
    {
        return getAsString<U>(value);
    }
    
    std::function<T()> GetValue;
    std::function<void(T)> SetValue;
private:
    template <CanString U>
    static std::string getAsString(U _value)
    {
        
        if constexpr (std::is_pointer<U>())
        {
            if(_value != nullptr)
            {
                PrintString(*_value);
            }
        }
        std::ostringstream oss;
        oss << _value;
        return oss.str();
    }
    
    
};





