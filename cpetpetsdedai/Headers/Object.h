#pragma once
#include "Type.h"

class Object {
public:
	Object() = default;
	Object(std::string typeName, Type* parentType);
	virtual ~Object() = default ;

	Type* GetType()
	{
		return &type;
	}

	static Type* ObjectType();

private:
	Type type;
	static Type objectType;

};
