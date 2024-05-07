#pragma once
#include <sstream>
#include <string>
#include "ISerialisable.h"

class BaseField: public ISerialisable {
public:
    BaseField() = default;
    BaseField(const std::string& _name) : name(_name) {}
    std::string name;
    virtual ~BaseField() {}

    virtual std::string GetValueAsString() = 0;

};


template <typename  T>
class Field : public BaseField
{
public:
    Field() {}
    Field(const std::string& _name) : BaseField(_name) {}
    Field(const std::string& _name, std::function<T()> _getValue, std::function<void(T)> _setValue) : BaseField(_name), GetValue(_getValue), SetValue(_setValue) {}
    ~Field() override {}

    std::string GetValueAsString() override
    {
        return getAsString(GetValue());
    }

    template <typename U>
    static std::string PrintString(U value)
    {
        return getAsString<U>(value);
    }
    
    std::function<T()> GetValue;
    std::function<void(T)> SetValue;
    
public:
    uint64_t Serialize(SerializeBuffer& buffer) override
    {
        if constexpr (isSerialisable<T>)
        {
            GetValue().Serialize(buffer);
            return 0;
        }
        if constexpr (std::is_pointer<T>())
        {
            //TODO Serialize
            return 0;
        }
        buffer.startBuffer << name << ": " << GetValueAsString() << "\n";
        return 0;
    }
    
    void Deserialize(const std::string& _serialised) override
    {
        
    }

private:
    template <typename U>
    static std::string getAsString(U _value)
    {
        if constexpr (std::is_pointer<U>())
        {
            if(_value != nullptr)
            {
                PrintString(*_value);
            }
        }
        if constexpr (CanString<U>)
        {
            std::ostringstream oss;
            oss << _value;
            return oss.str();
        }
        return "";
    }
};





