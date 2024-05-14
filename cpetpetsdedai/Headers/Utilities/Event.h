#pragma once
#include <iostream>
#include <map>
#include <functional>

template <typename... Args>
class Event
{
public:
	~Event();
	int currentCount = 0;
	template<typename Class>
	int Subscribe(void(Class::* funcToSubscribe)(Args...), Class* instance);
	int Subscribe(const std::function<void(Args...)>& funcToSubscribe);

	void Desubscribe(int id);
	void InvokeEvent(Args... args);

	void DesubscribeAll();

private:
	std::map<int,std::function<void(Args...)>> functionSubscribbed;
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
void Event<Args...>::Desubscribe(int id)
{
	for (int i = 0; i < functionSubscribbed.size(); i++)
	{
		if (functionSubscribbed[i].first == id)
		{
			functionSubscribbed.erase(functionSubscribbed.begin() + i);
			return;
		}
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
inline void Event<Args...>::DesubscribeAll()
{
	functionSubscribbed.clear();
}
