#pragma once
#include <string>

#include "../SerializeBuffer.h"

class ISerialisable {
public:
	virtual void Serialise(SerializeBuffer& buffer) = 0;
	virtual void Deserialise(const std::string& _serialised) = 0;
};
