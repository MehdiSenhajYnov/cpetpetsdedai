#pragma once
#include <functional>

class Object;

class TypeInfo
{
public:
    std::string Name;
    int Size;
    int Alignment;

    std::function<Object*()> ObjectConstructor { };
    
    template <typename T>
    static TypeInfo Create()
    {
        TypeInfo info;
        info.Name = typeid(T).name();
        info.Size = sizeof(T);
        info.Alignment = alignof(T);

        if constexpr (std::is_base_of_v<Object,T>)
        {
            info.ObjectConstructor = []() -> Object*
            {
                return new T();
            };
        }
        
        return info;
    }
};
