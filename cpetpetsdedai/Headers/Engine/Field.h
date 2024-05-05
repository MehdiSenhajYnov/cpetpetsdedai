#pragma once
#include <sstream>
#include <string>
#include <iostream>

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
    Field(const std::string& _name, T _value) : BaseField(_name), Tvalue(_value) {}
    ~Field() override {}
    std::string GetValueAsString() override
    {
        std::ostringstream oss;
        oss << Tvalue;
        return oss.str();
    }
    T GetValue() { return Tvalue; }
private:
    T Tvalue;
};





