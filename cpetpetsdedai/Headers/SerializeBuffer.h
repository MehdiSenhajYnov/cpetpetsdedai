#pragma once
#include <sstream>

struct SerializeBuffer {
	SerializeBuffer() = default;

	std::string startBuffer;
	std::string mainBuffer;
	std::string endBuffer;

	std::string GetAll()
	{
		return startBuffer + mainBuffer + endBuffer;
	}
};