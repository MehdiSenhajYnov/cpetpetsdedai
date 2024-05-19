#pragma once
#include "ISerialisable.h"

class BaseField: public ISerialisable {
public:
    BaseField() = default;
    BaseField(const std::string& _name) : name(_name) {}
    std::string name;
    virtual ~BaseField() override = default;

    virtual std::string GetValueAsString() = 0;
    virtual uint64_t Serialize(SerializeBuffer& buffer, const std::string_view _previousContent) override = 0;
    virtual bool Deserialize(const std::string& _serialised, const std::string& _serializeContext) override = 0;
    virtual bool DeserializeNoName(const std::string& _serialised, const std::string& _serializeContext) = 0;

};
