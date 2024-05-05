#pragma once
#include <string>
#include <map>
#include <iostream>
#include "../../Type.h"

#define AddType(Object, Value) \
static Type* GetStaticType() \
{ \
static Type _objtype(#Object, Value); \
return &_objtype; \
}

#define SerializeField(type, name) \
auto _change##name##Invoke = [this](type _newValue) \
{ \
this->name = _newValue; \
}; \
GetType()->CreateField<type>(#name, _change##name##Invoke)


class Object {
public:
	AddType(Object, nullptr)

	//Object(std::string typeName, Type* parentType);
	Type* GetType();
	
	virtual ~Object() = default ;

	int GetId() const { return id; }
	
private:
	uint64_t id;
	Type type;
	//static const Type objectType;
protected:
	void InitObject(const std::string& typeName, Type* parentType);

	Object(const std::string& typeName, Type* parentType, TList<BaseField*> fields);
	
	Object(const std::string& typeName, Type* parentType);
	Object(const int& _id,const std::string& typeName, Type* parentType);

	Object() = default;
};


template<typename T>
concept isObject =
	std::is_base_of_v<Object, T> &&
	std::is_convertible_v<const volatile T*, const volatile Object*>;
