#include "../Headers/Components/Animator.h"
#include "../Headers/Engine/GameManager.h"
#include "../Headers/Engine/GameObject.h"
#include "../Headers/Utilities/FileUtilities.h"

void TestSerialization()
{
	std::string_view curSerialization;
	
	GameObject gameObject = GameObject();

	// if constexpr (isBaseOf<Object, decltype(gameObject)>())
	// {
	// 	std::cout << "GameObject is convertible to Object" << std::endl;
	// }
	//
	// GameObject* gameObjectPtr = &gameObject;
	// if constexpr (isBaseOf<Object, decltype(gameObjectPtr)>())
	// {
	// 	std::cout << "GameObject* is convertible to Object*" << std::endl;
	// }
	//
	// GameObject** gameObjectPtrPtr = &gameObjectPtr;
	// if constexpr (isBaseOf<Object, decltype(gameObjectPtrPtr)>())
	// {
	// 	std::cout << "GameObject** is convertible to Object**" << std::endl;
	// }

	
	
	gameObject.Init("TestSerialisation");
	gameObject.SetPosition(sf::Vector2f(10, 10));
	gameObject.AddComponent<Animator>();
	
	std::cout << "Test Serialisation" << std::endl;
	SerializeBuffer buffer;
	uint64_t SaveObjId = GlobalSerializer::Serializer(buffer, gameObject, curSerialization);

	std::cout << "buffer start : " << std::endl;
	std::cout << buffer.startBuffer << std::endl;
	std::cout << "buffer main : " << std::endl;
	std::cout << buffer.mainBuffer << std::endl;
	std::cout << "buffer end : " << std::endl;
	std::cout << buffer.endBuffer << std::endl;
}

void DeserialisationTest()
{
	std::string sceneContent = FileUtilities::ReadFromFile("Scenes/TestScene.sc");

	auto splittedByNewElements = Utilities::SplitString(sceneContent, "--- ");
	
	std::string toFindGameObjectID = "!t!-1829605404";

	for (auto& serializedElement : splittedByNewElements)
	{
		if (serializedElement.find(toFindGameObjectID) != std::string::npos)
		{
			int indexOfNewLine = Utilities::IndexOf(serializedElement, "\n");
			std::string  serializedGameObject = serializedElement.substr(indexOfNewLine + 1);
			GameObject gameObject = GameObject();
			gameObject.Deserialize(serializedGameObject, sceneContent);
			std::cout << "GameObject found" << std::endl;


			// on resérialize pour voir si le contenu est le même
			SerializeBuffer buffer;
			gameObject.Serialize(buffer, "");
			FileUtilities::WriteInFile("Scenes/TestDeserialization.sc", buffer.startBuffer + buffer.mainBuffer + buffer.endBuffer);
			break;
		}
		
	}

}



int main()
{
	//DeserialisationTest();


	GameManager gameManager;
	gameManager.Run();
	return 0;
}
