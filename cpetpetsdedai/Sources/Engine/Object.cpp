#include <utility>

#include "../../Headers/Engine/Object.h"

Object::Object(const std::string& typeName, Type* parentType): Object( Utilities::GenerateUniqueId(), typeName, parentType)
{
}

Object::Object(const uint64_t& _id, const std::string& typeName, Type* parentType) : id(_id), type(typeName, parentType)
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

uint64_t Object::GetId() const
{
	return id;
}

uint64_t Object::Serialize(SerializeBuffer& buffer, const std::string_view _previousContent)
{
	static const std::string NEWLINE_PREFIX = "--- ";
	static const std::string TYPE_PREFIX = "!t!";
	static const std::string ID_PREFIX = "!i!";
		
	buffer.mainBuffer += NEWLINE_PREFIX + TYPE_PREFIX + std::to_string(GetType()->GetId()) + ID_PREFIX + std::to_string(GetId()) + "\n";
		
	buffer.mainBuffer += ("id: " + std::to_string(id) + "\n");
	for (auto& _field : GetType()->GetAllFields())
	{
		buffer.mainBuffer += (_field->name + ": ");
		_field->Serialize(buffer, _previousContent);
		buffer.mainBuffer += "\n";
	}
	return id;
}

void Object::Deserialize(const std::string& _serialised, const std::string& _serializeContext)
{
	std::vector<std::string> _serialisedLines = Utilities::SplitString(_serialised, "\n");
	for (const auto& line : _serialisedLines)
	{
		auto splitLine = Utilities::SplitString(line, ": ");
		if (!splitLine.empty())
		{
			for (auto& _field : GetType()->GetAllFields())
			{
				if (splitLine[0] == _field->name)
				{
					_field->Deserialize(line, _serializeContext);
				}
			}
		}
	}
		
}

void Object::Deserialize(const TList<std::string>& _serialised)
{
}
