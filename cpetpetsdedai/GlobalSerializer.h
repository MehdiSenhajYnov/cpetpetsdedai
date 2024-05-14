#pragma once
#include <cstdint>
#include <string>
#include "Headers/SerializeBuffer.h"
#include "Headers/Utilities/AllConcepts.h"
#include "Headers/Utilities/Utilities.h"

class GlobalSerializer
{
public:
    template <typename T>
    static uint64_t Serializer(SerializeBuffer& buffer, T& object, const std::string_view& _previousContent)
    {
        if constexpr (std::is_pointer<T>())
        {
            if (object == nullptr)
            {
                buffer.mainBuffer += "nullptr";
                return 0;
            }
            if (IsOrIsPointerSerializable<T>(object))
            {
                SerializeBuffer tempBuffer;
                std::string temp = buffer.mainBuffer + buffer.endBuffer + buffer.startBuffer + std::string(_previousContent);
                uint64_t objID = GlobalSerializer::SerializePointerValue(tempBuffer, object, temp);
                buffer.mainBuffer += std::to_string(objID);
                buffer.endBuffer += tempBuffer.mainBuffer;
            } else
            {
                std::cout << "pointer not serializable" << std::endl;
            }
        }
        else if constexpr (IsSerialisable<T>)
        {
            return object.Serialize(buffer, _previousContent);
        }
        else if constexpr (IsVector<T>)
        {
            std::cout << "Serializing vector : " << typeid(T).name() << std::endl;
            SerializeVector(object, buffer, _previousContent);
            return true;
        }
        else if constexpr (CanString<T>)
        {
            buffer.mainBuffer += Utilities::ToString(object);
        }
        else
        {
            std::cout << "WARNING : "<< typeid(object).name() <<" is not serializable !" << std::endl;
        }
        return 0;
    }

    template <typename T>
    static uint64_t SerializePointerValue(SerializeBuffer& buffer, T _obj, const std::string_view _previousContent)
    {

        if constexpr (IsBaseOf<class Object, T>)
        {
            if (CheckAlreadySerialized(_obj->GetId(), buffer, _previousContent))
            {
                return _obj->GetId();
            }
        }
        
        if (IsOrIsPointerSerializable(_obj))
        {
            return _obj->Serialize(buffer, _previousContent);
        }
        
        if constexpr (CanString<T>)
        {
            buffer.mainBuffer += Utilities::ToString(_obj);
            return 0;
        }

        return 0;
    }

    template <template <typename,typename> class VectorClass, typename ElementType, typename VectorAllocator>
    static uint64_t SerializeVector(const VectorClass<ElementType, VectorAllocator>& outVar, SerializeBuffer& buffer, const std::string_view _previousContent)
    requires (IsVector<VectorClass<ElementType, VectorAllocator>>)
    {
        buffer.mainBuffer += "[ ";
        
        for (int i = 0; i < outVar.size(); ++i)
        {
            GlobalSerializer::Serializer(buffer, outVar[i], _previousContent);
            if (i != outVar.size() - 1)
            {
                buffer.mainBuffer += " !&! ";
            }
        }
        
        buffer.mainBuffer += " ]";
        return 0;
    }

        
    template <typename T>
    static bool IsOrIsPointerSerializable(T& object)
    {
        if constexpr (std::is_pointer<T>())
        {
            return IsOrIsPointerSerializable(*object);
        }
        if (IsSerialisable<T>)
        {
            return true;
        }
        return false;
    }

    
    static bool CheckAlreadySerialized(const uint64_t _idToCheck, const SerializeBuffer& _buffer, const std::string_view _previousContent)
    {
        std::string Tofind = "!i!" + std::to_string(_idToCheck);
        if (_buffer.mainBuffer.find(Tofind) != std::string::npos)
        {
            return true;
        }
        if (_previousContent.find(Tofind) != std::string::npos)
        {
            return true;
        }
        return false;
    }
    
};
