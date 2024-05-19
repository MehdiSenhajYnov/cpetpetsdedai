#pragma once
#include <stdexcept>
#include "Factory.h"
#include "Headers/Engine/TypeContainer.h"
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
            return GlobalDeserializer::DeserializePointer(varInfo, outVar, _serialised, _serializeContext);
        }
        else if constexpr (IsBaseOf<ISerialisable, T> || IsSerialisable<T>)
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
            DeserializeVector(outVar, varInfo, _serializeContext);
            return true;
        }
        else if constexpr (IsDerivedFrom<T, BaseEvent>)
        {
            return DeserializeEvent(outVar, varInfo, _serializeContext);
        }
        else if constexpr (CanString<T>)
        {
            std::istringstream inputStream(varInfo);
            inputStream >> outVar;
            return true;
        }

        return false;
    }

    template <template <typename,typename> typename VectorClass, typename ElementType, typename VectorAllocator>
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
    static bool DeserializePointer(const std::string& _varInfo, T& outVar, const std::string& _serialised, const std::string& _serializeContext, const std::string& name = "")
    {
        if (_varInfo == "nullptr")
        {
            outVar = nullptr;
            return true;
        }

        if constexpr (!IsBaseOf<Object, T>)
        {
            return false;
        }
        
        uint64_t id = std::stoull(_varInfo);
        if (Factory::GetInstance()->GetObjectById().contains(id))
        {
            outVar = static_cast<T>(Factory::GetInstance()->GetObjectById()[id]);
            return true;
        }
        std::string selectedObjectSerialized = GetSerializdObjectById(id, _serializeContext);

        uint64_t startIndexOfType = selectedObjectSerialized.find("--- !t!");
        uint64_t endIndexOfType = selectedObjectSerialized.find("!i!");
        if (startIndexOfType == std::string::npos || endIndexOfType == std::string::npos)
        {
            return false;
        }
        std::string typeName = selectedObjectSerialized.substr(startIndexOfType + 7, endIndexOfType - startIndexOfType - 7);

        if (!Factory::GetInstance()->CanBeCreated(typeName))
        {
            throw std::runtime_error(std::string("DESERIALISATION ERROR : OBJECT TYPE NOT REGISTERED : ") + typeName);
            return false;
        }
        
        Object* wantedObj = Factory::GetInstance()->CreateObjectByName(typeName, id);
        GlobalDeserializer::DeserializeCaller(wantedObj, selectedObjectSerialized, _serializeContext);
        
        outVar = static_cast<T>(wantedObj);
        return true;
    }

    template <typename T>
    static void DeserializeCaller(T& outVar, const std::string& _serialised, const std::string& _serializeContext)
    {
        outVar->Deserialize(_serialised, _serializeContext);
    }

    template <typename T>
    static bool DeserializeEvent(T& outVar, const std::string& _serialised, const std::string& _serializeContext)
    {
        bool result = GlobalDeserializer::Deserialize(outVar.GetSerializableFunctionNames(), _serialised, _serializeContext);
        outVar.SubscribeAllSerializablesList();
        return result;
    }


    static std::string GetSerializdObjectById(uint64_t id, const std::string& _serializeContext)
    {
        auto splittedContext = Utilities::SplitString(_serializeContext, "\n");
        bool found = false;
        std::string result;
        for (const auto& line : splittedContext)
        {
            // Si on a pas encore trouvé l'objet, on cherche l'id  // NOLINT(clang-diagnostic-invalid-utf8)
            if (!found)
            {
                if (line.find("!i!" + std::to_string(id)) != std::string::npos)
                {
                    found = true;
                }
            // Si on a trouvé l'objet, on ajoute les lignes jusqu'à la fin de l'objet  // NOLINT(clang-diagnostic-invalid-utf8)
            } else if (line.find("--- !t!") != std::string::npos)
            {
                break;
            }
            if (found)
            {
                result += line + "\n";
            }
        }
        return result;
    }
    
};