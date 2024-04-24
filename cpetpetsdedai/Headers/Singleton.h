#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "Object.h"

template<typename T>
class Singleton : public Object
{
public:
	static T* Instance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}
	~Singleton()
	{
	}
protected:
	Singleton() : Object("Singleton", Object::ObjectType())
	{
	}
	Singleton(const std::string& typeName) : Object(typeName, &singletonType)
	{
	}
	static T* instance;
private:
	Type singletonType = Type("Singleton", Object::ObjectType());
};



