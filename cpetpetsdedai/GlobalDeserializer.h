#pragma once
#include <cstdint>
#include <string>

#include "Factory.h"
#include "Headers/SerializeBuffer.h"
#include "Headers/Utilities/AllConcepts.h"
#include "Headers/Utilities/Utilities.h"


class GlobalDeserializer
{
public:

    template <typename T>
    static bool Deserialize(T& outVar, const std::string& _serialised, const std::string& _serializeContext, const std::string& name = "")
    {
        std::string varInfo;
        if (!name.empty())
        {
            varInfo = _serialised.substr(name.size() + 2);
        } else
        {
            varInfo = _serialised;
        }
        if constexpr (std::is_pointer<T>())
        {
            if (varInfo == "nullptr")
            {
                outVar = nullptr;
                return true;
            }

            if constexpr (IsBaseOf<class Object, T>)
            {
                uint64_t id = std::stoull(varInfo);
                if (Factory::GetInstance()->GetObjectById().contains(id))
                {
                    outVar = static_cast<T>(Factory::GetInstance()->GetObjectById()[id]);
                    return true;
                }
                else
                {
                    using objecType = std::remove_pointer_t<T>;
                    outVar = Factory::GetInstance()->CreateObject<objecType>(id);
                    return true;
                }
            }
        }
        else if constexpr (IsBaseOf<class ISerialisable, T> || IsSerialisable<T>)
        {
            outVar.Deserialize(varInfo, _serializeContext);
            return true;
        }
        else if constexpr (std::is_enum<T>())
        {
            outVar = static_cast<T>(std::stoi(varInfo));
            return true;
        }
        else if constexpr (IsVector<T>)
        {
            std::cout << "Deserializing vector" << std::endl;
            DeserializeVector(outVar, varInfo, _serializeContext);
            return true;
        }
        else if constexpr (CanString<T>)
        {
            std::istringstream inputStream(varInfo);
            inputStream >> outVar;
            return true;
        }

        return false;
    }

    template <template <typename,typename> class VectorClass, typename ElementType, typename VectorAllocator>
    static void DeserializeVector(VectorClass<ElementType, VectorAllocator> &outVar, const std::string& _serialised, const std::string& _serializeContext, const std::string& name = "")
    requires (IsVector<VectorClass<ElementType, VectorAllocator>>)
    {
        std::string _serialisedNoBrackets = _serialised.substr(2, _serialised.size() - 4);
        std::vector<std::string> _split = Utilities::SplitString(_serialisedNoBrackets, " !&! ");
        for (const auto& element : _split)
        {
            ElementType temp;
            Deserialize(temp, element, _serializeContext);
            outVar.push_back(temp);
        }
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
