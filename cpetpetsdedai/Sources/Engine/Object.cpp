#include <utility>
#include "../../Headers/Engine/Object.h"

Object::Object(const std::string& typeName, Type* parentType): id(Utilities::GenerateUniqueId()),
                                                               type(typeName, parentType)
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

void Object::SetId(uint64_t _id)
{
	if (id == _id)
	{
		return;
	}
	onIdChanged.InvokeEvent(id, _id);
	id = _id;
}

uint64_t Object::Serialize(SerializeBuffer& buffer, const std::string_view _previousContent)
{
	if (!CanBeSerialized) return -1;
	static const std::string NEWLINE_PREFIX = "--- ";
	static const std::string TYPE_PREFIX = "!t!";
	static const std::string ID_PREFIX = "!i!";
		
	buffer.mainBuffer += NEWLINE_PREFIX + TYPE_PREFIX + GetType()->GetName() + ID_PREFIX + std::to_string(GetId()) + "\n";
		
	buffer.mainBuffer += ("id: " + std::to_string(id) + "\n");
	for (auto& _field : GetType()->GetAllFields())
	{
		buffer.mainBuffer += (_field->name + ": ");
		_field->Serialize(buffer, _previousContent);
		buffer.mainBuffer += "\n";
	}
	return id;
}

bool Object::Deserialize(const std::string& _serialised, const std::string& _serializeContext)
{
	bool result = true;
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
					bool tempResult = _field->Deserialize(line, _serializeContext);
					if (!tempResult)
					{
						result = false;
					}
				}
			}
		}
	}
	return result;
}

// void Object::Deserialize(const TList<std::string>& _serialised)
// {
// }
