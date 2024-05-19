#pragma once
#include "Assets/../Type.h"

class GlobalDeserializerzz
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
            GlobalDeserializer::DeserializePointer(varInfo, outVar, _serialised, _serializeContext);
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
    static bool DeserializePointer(std::string varInfo, T& outVar, const std::string& _serialised, const std::string& _serializeContext, const std::string& name = "")
    {
        if (varInfo == "nullptr")
        {
            outVar = nullptr;
            return true;
        }

        if constexpr (!IsBaseOf<Object, T>)
        {
            return false;
        }
        
        uint64_t id = std::stoull(varInfo);
        if (Factory::GetInstance()->GetObjectById().contains(id))
        {
            outVar = static_cast<T>(Factory::GetInstance()->GetObjectById()[id]);
            return true;
        }
        std::string selectedObjectSerialized = GetSerializdObjectById(id, _serializeContext);

        int startIndexOfType = selectedObjectSerialized.find("--- !t!");
        int endIndexOfType = selectedObjectSerialized.find("!i!");
        if (startIndexOfType == std::string::npos || endIndexOfType == std::string::npos)
        {
            return false;
        }
        std::string objectId = selectedObjectSerialized.substr(startIndexOfType + 7, endIndexOfType - startIndexOfType - 7);
        Object* object = Factory::GetInstance()->CreateObjectByName(objectId, id);
        
        //Type::GetAllTypesById().contains(objectId);

        //Object::Deserialize()
    
        using objecType = std::remove_pointer_t<T>;
        outVar = Factory::GetInstance()->CreateObject<objecType>(id);
        return true;
    }



    static std::string GetSerializdObjectById(uint64_t id, const std::string& _serializeContext)
    {
        auto splittedContext = Utilities::SplitString(_serializeContext, "\n");
        bool found = false;
        std::string result;
        for (const auto& line : splittedContext)
        {
            // Si on a pas encore trouvé l'objet, on cherche l'id
            if (!found)
            {
                if (line.find("!i!" + std::to_string(id)) != std::string::npos)
                {
                    found = true;
                }
            // Si on a trouvé l'objet, on ajoute les lignes jusqu'à la fin de l'objet
            } else if (line.find("--- !t!") != std::string::npos)
            {
                break;
            } else
            {
                result += line + "\n";
            }
        }
        return result;
    }
    
};
