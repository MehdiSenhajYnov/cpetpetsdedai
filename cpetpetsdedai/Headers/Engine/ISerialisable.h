#pragma once
#include <string>

#include "../SerializeBuffer.h"

class ISerialisable {
public:
	virtual uint64_t Serialize(SerializeBuffer& buffer) = 0;
	virtual void Deserialize(const std::string& _serialised) = 0;
	
};
