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
private:\
inline static Type _objtype = Type(#Object, Value::GetStaticType()); \
public:\
static Type* GetStaticType() \
{ \
return &_objtype; \
}

#define AddTypeNoParent(Object) \
private:\
inline static Type _objtype = Type(#Object, nullptr); \
public:\
static Type* GetStaticType() \
{ \
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
	// friend std::ostream& operator<<(std::ostream& _os, const Object& _obj)
	// {
	// 	Object& _objRef = const_cast<Object&>(_obj);
	// 	std::cout << "id: " << _obj.id << std::endl;
	// 	_os << "id: " << _obj.id;
	// 	
	// 	for (auto& _field : _objRef.GetType()->GetAllFields())
	// 	{
	// 		_os << (_field->name + ": " + _field->GetValueAsString() + "\n");
	// 	}
	// 	
	// 	return _os;		
	// }

public:
	private: inline static Type _objtype = Type("Object", nullptr); public: static Type* GetStaticType() { return &_objtype; }
	//Object(std::string typeName, Type* parentType);
	Type* GetType();

	virtual void PreDestroy() {}
	virtual ~Object() override = default ;

	[[nodiscard]] uint64_t GetId() const;

public:

	virtual uint64_t Serialize(SerializeBuffer& buffer, const std::string_view _previousContent) override;

	virtual bool Deserialize(const std::string& _serialised, const std::string& _serializeContext) override;

	virtual void Deserialize(const TList<std::string>& _serialised);

private:
	uint64_t id;
	Type type;
protected:
	void InitObject(const std::string& typeName, Type* parentType);

	Object(const std::string& typeName, Type* parentType, TList<BaseField*> fields);
	
	Object(const std::string& typeName, Type* parentType);
	Object(const uint64_t& _id,const std::string& typeName, Type* parentType);
	
	Object() = default;
	
};



