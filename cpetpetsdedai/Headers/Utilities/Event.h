#pragma once
#include <iostream>
#include <map>
#include <functional>
#include "../Engine/MethodContainer.h"
#include "../../TList.h"

class BaseEvent
{
};

template <typename... Args>
class Event : public BaseEvent
{
public:
	Event() = default;
	~Event();

	int currentCount = 0;
	template<typename Class>
	int Subscribe(void(Class::* funcToSubscribe)(Args...), Class* instance);
	int Subscribe(const std::function<void(Args...)>& funcToSubscribe);

	void Unsubscribe(int id);
	void InvokeEvent(Args... args);

	void DesubscribeAll();

	int SubscribeSerializable(std::string _name)
	{
		if (MethodContainer::GetFunctionsWith<void, Args...>().contains(_name))
		{
			currentCount++;
			functionSubscribbed[currentCount] = MethodContainer::GetFunctionsWith<void, Args...>()[_name];
			serializableFunctionNames.push_back(_name);
			return currentCount;
		}
		return -1;
	}

	void SubscribeAllSerializablesList()
	{
		for (auto& _name : serializableFunctionNames)
		{
			if (MethodContainer::GetFunctionsWith<void, Args...>().contains(_name))
			{
				currentCount++;
				functionSubscribbed[currentCount] = MethodContainer::GetFunctionsWith<void, Args...>()[_name];
			}
		}
	}
	
	TList<std::string>& GetSerializableFunctionNames()
	{
		return serializableFunctionNames;
	}
private:
	std::map<int,std::function<void(Args...)>> functionSubscribbed = std::map<int,std::function<void(Args...)>>();
	TList<std::string> serializableFunctionNames = TList<std::string>();
};

template <typename ... Args>
Event<Args...>::~Event()
{
	DesubscribeAll();
}

template <typename... Args>
template<typename Class>
int Event<Args...>::Subscribe(void(Class::*funcToSubscribe)(Args...), Class* instance)
{
	currentCount++;
	std::function<void(Args...)> lambda = [funcToSubscribe, instance](Args... args) {
        (instance->*funcToSubscribe)(args...);
    };
    functionSubscribbed[currentCount] = lambda;
	return currentCount;
}

template <typename ... Args>
int Event<Args...>::Subscribe(const std::function<void(Args...)>& funcToSubscribe)
{
	currentCount++;
	functionSubscribbed[currentCount] = funcToSubscribe;
	return currentCount;
}

template <typename ... Args>
void Event<Args...>::Unsubscribe(int id)
{
	if (functionSubscribbed.contains(id))
	{
		functionSubscribbed.erase(id);
	}
}

template<typename ...Args>
void Event<Args...>::InvokeEvent(Args ...args)
{

	if (functionSubscribbed.size() > 741382308990216) return;

	if (functionSubscribbed.size() > 0)
	{
		for(auto& [id, functionToCall] : functionSubscribbed)
		{
			if (functionToCall == nullptr) continue;
			functionToCall(args...);
			
		}
	}
}

template<typename ...Args>
void Event<Args...>::DesubscribeAll()
{
	functionSubscribbed.clear();
}
