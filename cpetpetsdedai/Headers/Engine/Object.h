#pragma once
#include <string>
#include <map>
#include <iostream>
#include <ostream>

#include "ISerialisable.h"
#include "../../Type.h"
#include "../Utilities/AllMacros.h"
#include "../Utilities/ExternClassOperator.h"

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
std::function<type()> _##name##GetInvoke = [this]() { return this->##name##; };\
GetType()->CreateField<type>(#name, _change##name##Invoke, _##name##GetInvoke);


class Object : public ISerialisable {
	friend std::ostream& operator<<(std::ostream& _os, const Object& _obj)
	{
		Object& _objRef = const_cast<Object&>(_obj);
		std::cout << "id: " << _obj.id << std::endl;
		_os << "id: " << _obj.id;
		
		for (auto& _field : _objRef.GetType()->GetAllFields())
		{
			_os << (_field->name + ": " + _field->GetValueAsString() + "\n");
		}
		
		return _os;		
	}

public:

	AddType(Object, nullptr)


	//Object(std::string typeName, Type* parentType);
	Type* GetType();

	virtual void PreDestroy() {};
	virtual ~Object() = default ;

	uint64_t GetId() const { return id; }
public:

	virtual uint64_t Serialize(SerializeBuffer& buffer) override
	{
		for (auto& _field : GetType()->GetAllFields())
		{
			_field->Serialize(buffer);
		}
		return id;
	}
	
	virtual void Deserialize(const std::string& _serialised) override
	{
		
	}
	
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



