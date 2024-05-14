#pragma once
#include <string>
#include "../SerializeBuffer.h"
#include "../Utilities/AllConcepts.h"

class ISerialisable {
public:
	virtual          ~ISerialisable() = default;
	virtual uint64_t Serialize(SerializeBuffer& buffer, const std::string_view _previousContent) = 0;
	virtual bool     Deserialize(const std::string& _serialised, const std::string& _serializeContext) = 0;
};
