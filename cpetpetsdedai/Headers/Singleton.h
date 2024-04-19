#pragma once
#include <iostream>
#include <vector>
#include <functional>

template<typename Class>
class Singleton
{
private:
	static Class* instance;
public:
	virtual ~Singleton();
	static Class* Instance();
};

template <typename Class>
Class* Singleton<Class>::Instance()
{
	if (instance == nullptr)
	{
		instance = new Class();
	}
	return instance;
}
