#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <ostream>

#include "Headers/Utilities/AllConcepts.h"
#include "Headers/SerializeBuffer.h"
#include "Headers/Engine/ISerialisable.h"


template<typename T>
class TList : public std::vector<T>, public ISerialisable
{

public:
    TList(std::initializer_list<T> List) : std::vector<T>(List){}
    TList() : std::vector<T>(){}
    
    void RemoveElement(const T& element) {
        this->erase(std::remove(this->begin(), this->end(), element), this->end());
    }
    
    bool RemoveFirstWith(const std::function<bool(const T&)>& _predicate)
    {
        auto it = std::find_if(this->begin(), this->end(), _predicate);
        if (it != this->end()) {
            this->erase(it);
            return true;
        }
        return false;
    }

    bool RemoveFirstWith(const std::function<bool(const T&)>& _predicate, T& RemovedValue)
    {
        auto it = std::find_if(this->begin(), this->end(), _predicate);
        if (it != this->end()) {
            RemovedValue = *it;
            this->erase(it);
            return true;
        }
        return false;
    }

    void RemoveAllWith(const std::function<bool(const T&)>& _predicate)
    {
        this->erase(std::remove_if(this->begin(), this->end(), _predicate), this->end());
    }

    
    bool Contains(const std::function<bool(const T&)>& _predicate)
    {
        if (std::count(this->begin(), this->end(), _predicate)) {
            return true;
        }
        else {
            return false;
        }
    }

    T GetFirstWith(const std::function<bool(const T&)>& _predicate)
    {
        auto it = std::find_if(this->begin(), this->end(), _predicate);
        if (it != this->end()) {
            return *it;
        }
        return nullptr;
    }
    
    TList<T> GetAllWith(const std::function<bool(const T&)>& _predicate)
    {
        std::vector<T> result;
        for (const T& element : *this) {
            if (_predicate(element)) {
                result.push_back(element);
            }
        }
        return result;
    }

    void AppendVector(const std::vector<T>& _list)
    {
        this->insert(this->end(), _list.begin(), _list.end());

    }

public:
    uint64_t Serialize(SerializeBuffer& buffer) override
    {
        if constexpr (isSerialisable<T>)
        {
            _objectSerialize(buffer);
            return 0;
        }
        if constexpr (std::is_pointer<T>())
        {
            if constexpr (isSerialisable<decltype(*std::declval<T>())>)
            {
                _objectPointerSerialize(buffer);
                return 0;
            }
        }
        if constexpr (CanString<T>)
        {
            _standardSerialize(buffer);
        }

        return 0;
    }
    
    void Deserialize(const std::string& _serialised) override
    {
        
    }

private:
    void _standardSerialize(SerializeBuffer& buffer)
    {
        buffer.startBuffer << "[ ";
        for (const T& element : *this) {
            //buffer.mainBuffer << element << " !&! ";
        }
        buffer.endBuffer << " ]";
    }

    void _objectSerialize(SerializeBuffer& buffer)
    {
        buffer.startBuffer << "[ ";
        for (const T& element : *this) {
            element.Serialize(buffer);
            //buffer.mainBuffer << " !&! ";
        }
        buffer.endBuffer << " ]";
    }

    void _objectPointerSerialize(SerializeBuffer& buffer)
    {
        buffer.startBuffer << "[ ";

        TList<uint64_t> ids;
        
        SerializeBuffer tempBuffer;
        for (const T& element : *this) {
            uint64_t elementID = element->Serialize(tempBuffer);
            ids.push_back(elementID);
            buffer.endBuffer << tempBuffer.startBuffer.str();
        }

        ids.Serialize(buffer);
        
        buffer.endBuffer << " ]";
    }

    void _pointerSerialize(SerializeBuffer& buffer, T& _value)
    {
        buffer.startBuffer << "[ ";
        for (const T& element : *this) {
            //buffer.mainBuffer << *element << " !&! ";
        }
        buffer.endBuffer << " ]";
    }
};

