﻿#pragma once
#include <vector>
#include <algorithm>
#include <functional>

template<typename T>
class TList : public std::vector<T>
{
public:

    void RemoveElement(const T& element) {
        erase(std::remove(this->begin(), this->end(), element), this->end());
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

    
};

