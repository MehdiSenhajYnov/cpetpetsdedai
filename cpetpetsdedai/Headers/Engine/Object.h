#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>

#define AddType(Object, Value) \
static Type* GetStaticType() \
{ \
static Type _objtype(#Object, Value); \
return &_objtype; \
}

class Type {
public:
	Type(const std::string& name, Type* parent);
	static std::string TestValue();

	std::string GetName();
	Type* GetParent();
	bool Equals(const Type& Other) const;
	bool Equals(const Type* _other) const;
	
	static int typeCount;
	static std::map<std::string, Type*> allTypes;
	static Type* GetType(const std::string& name);
	static std::vector<Type*> GetAllChildren(const Type& parent);
	static bool IsOrIsDescendantOf(const Type* child, const Type* parent);
	
private:
	std::string name;
	Type *parent = nullptr;
};


class Object {
public:
	AddType(Object, nullptr)

	//Object(std::string typeName, Type* parentType);
	virtual ~Object() = default ;
	Type* GetType();
private:
	Type type;
	//static const Type objectType;
protected:
	void InitObject(std::string typeName, Type* parentType);
	Object(std::string typeName, Type* parentType);
	Object() = default;
};
