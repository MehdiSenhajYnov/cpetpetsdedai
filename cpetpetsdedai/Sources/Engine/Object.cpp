#include <utility>

#include "../../Headers/Engine/Object.h"

Object::Object(const std::string& typeName, Type* parentType): type(typeName, parentType)
{
}

Object::Object(const int& _id, const std::string& typeName, Type* parentType) : id(_id), type(typeName, parentType)
{
}

void Object::InitObject(const std::string& typeName, Type* parentType)
{
	type = Type(typeName, parentType);
}

Object::Object(const std::string& typeName, Type* parentType, TList<BaseField*> fields) : type(typeName, parentType)
{
	
}



Type* Object::GetType()
{
	return &type;
}
