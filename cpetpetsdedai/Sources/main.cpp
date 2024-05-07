#include "../Headers/Engine/GameManager.h"
#include "../Headers/Engine/GameObject.h"

int main()
{
	// GameObject gameObject = GameObject();
	// GameObject* goPointer = &gameObject;
	//
	// int testInt = 5;
	// int* testIntPointer = &testInt;
	// std::cout << "Test Serialisation" << std::endl;
	// SerializeBuffer buffer;
	// std::cout << "GameObject: ";
	// ISerialisable::Serializer(buffer, gameObject);
	// std::cout << "GameObject Pointer: ";
	// ISerialisable::Serializer(buffer, goPointer);
	// std::cout << "Int: ";
	// ISerialisable::Serializer(buffer, testInt);
	// std::cout << "Int Pointer: ";
	// ISerialisable::Serializer(buffer, testIntPointer);
	//
	GameManager gameManager;
	gameManager.Run();
	return 0;
}
