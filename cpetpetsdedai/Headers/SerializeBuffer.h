#pragma once
#include <sstream>

struct SerializeBuffer {
	SerializeBuffer() = default;

	std::stringstream startBuffer;
	std::stringstream mainBuffer;
	std::stringstream endBuffer;
};