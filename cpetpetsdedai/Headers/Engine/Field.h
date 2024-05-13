#pragma once
#include <sstream>
#include <string>
#include "ISerialisable.h"
#include <cstdint>

#include "../../GlobalDeserializer.h"
#include "../../GlobalSerializer.h"

class BaseField: public ISerialisable {
public:
    BaseField() = default;
    BaseField(const std::string& _name) : name(_name) {}
    std::string name;
    virtual ~BaseField() {}

    virtual std::string GetValueAsString() = 0;
    virtual uint64_t Serialize(SerializeBuffer& buffer, const std::string_view _previousContent) override = 0;
    virtual void Deserialize(const std::string& _serialised, const std::string& _serializeContext) override = 0;
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
    uint64_t Serialize(SerializeBuffer& buffer, const std::string_view _previousContent) override
    {
        auto value = GetValue();
        GlobalSerializer::Serializer(buffer, value, _previousContent);
        return 0;
    }
    
    void Deserialize(const std::string& _serialised, const std::string& _serializeContext) override
    {
        T temp;
        bool result = GlobalDeserializer::Deserialize(temp, _serialised, _serializeContext, name);
        if(result)
        {
            SetValue(temp);
        }
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





