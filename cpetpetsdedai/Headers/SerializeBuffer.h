#pragma once
#include <ostream>

struct SerializeBuffer {
	SerializeBuffer() = default;

	std::stringstream startBuffer;
	std::stringstream mainBuffer;
	std::stringstream endBuffer;
};
