#include "../Headers/Engine/GameManager.h"

class TestClass
{
public:
	TestClass() = default;

	TestClass(int _id, const std::string& _name, bool _isActive)
		: id(_id),
		  name(_name),
		  isActive(_isActive)
	{
	}

	int id = 0;
	std::string name = "Test";
	bool isActive = true;
	
};

int main()
{
	void* test = nullptr;
	TestClass obj(1, "Test", true);
	test = &obj;

	
	return 0;
}



