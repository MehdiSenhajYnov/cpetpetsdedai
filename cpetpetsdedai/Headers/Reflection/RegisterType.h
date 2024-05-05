#pragma once
#include <string>
#include "TypeId.h"
using std::string;


template <typename T>
class RegisterType
{
private:
    class RegisterTypeOnce
    {
    public:
        RegisterTypeOnce()
        {
            TypeId::RegisterTypeId<T>();
        }
    };
    inline static RegisterTypeOnce Registerer{};
};

#define REGISTER_TYPE_INTERNAL(TYPE,VARNAME) RegisterType<TYPE> VARNAME##TYPE {};
#define REGISTER_TYPE(TYPE) REGISTER_TYPE_INTERNAL(TYPE,TYPE##Registerer)
