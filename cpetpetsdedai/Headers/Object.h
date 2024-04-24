#pragma once
#include <string>
#include <map>
#include <iostream>

class Type {
public:
	Type(const std::string& name, Type* parent);

	std::string GetName();
	Type* GetParent();
	bool Equals(const Type& Other) const;

	static int typeCount;
	static std::map<std::string, Type*> allTypes;
	static Type* GetType(const std::string& name, Type* parent = nullptr);
private:
	std::string name;
	Type *parent = nullptr;
};


class Object {
public:
	Object() = default;
	Object(std::string typeName, Type* parentType);
	virtual ~Object() = default ;
	void Init(std::string typeName, Type* parentType);

	Type* GetType();

	static Type* ObjectType();

private:
	Type type;
	static Type objectType;

};
