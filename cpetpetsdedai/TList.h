#pragma once
#include <vector>
#include <algorithm>
#include <functional>

template<typename T>
class TList : public std::vector<T>
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

    bool Contains(const T& element)
    {
        if (std::count(this->begin(), this->end(), element)) {
            return true;
        }
        return false;
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

    // uint64_t Serialize(SerializeBuffer& buffer, const std::string_view _previousContent)
    // {
    //     buffer.mainBuffer += "[ ";
    //     
    //     for (int i = 0; i < this->size(); ++i)
    //     {
    //         GlobalSerializer::Serializer(buffer, this->at(i), _previousContent);
    //         if (i != this->size() - 1)
    //         {
    //             buffer.mainBuffer += " !&! ";
    //         }
    //     }
    //     
    //     buffer.mainBuffer += " ]";
    //     return 0;
    // }
    //
    // void Deserialize(const std::string& _serialised, const std::string& _serializeContext)
    // {
    //     std::string _serialisedNoBrackets = _serialised.substr(2, _serialised.size() - 4);
    //     std::vector<std::string> _split = Utilities::SplitString(_serialisedNoBrackets, " !&! ");
    //     for (const auto& element : _split)
    //     {
    //         T temp;
    //         GlobalDeserializer::Deserialize(temp, element, _serializeContext);
    //         this->push_back(temp);
    //     }
    // }

private:

};

