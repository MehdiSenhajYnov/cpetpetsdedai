#include "../../Headers/Scenes/Scene.h"

#include "../../CameraManager.h"
#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/Component.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Engine/GameObject.h"

Scene::Scene() : Scene("Scene", Object::GetStaticType())
{
}

Scene::Scene(std::string _typeName, Type* parentType) : Object(_typeName, parentType), mainCameraObject(nullptr),
                                                        mainCamera(nullptr),
                                                        sceneChanged(false),
                                                        window(nullptr)
{
	sceneFileEditor.SetCurrentScene(this);
}

GameObject* Scene::CreateGameObject(std::string _gameObjectName)
{
	GameObject* newGameObject = new GameObject();
	newGameObject->Init(_gameObjectName);
	gameObjectsToAdd.push_back(newGameObject);
	sceneFileEditor.CreateObject(newGameObject);
	return newGameObject;
}

GameObject* Scene::CreateGameObjectImmediate(std::string _gameObjectName)
{
	GameObject* newGameObject = new GameObject();
	newGameObject->Init(_gameObjectName);
	gameObjects.push_back(newGameObject);
	sceneFileEditor.CreateObject(newGameObject);
	//gamesObjectsComponents[newGameObject] = std::vector<Component*>();
	return newGameObject;
}

Scene::~Scene()
{
	std::cout << "Cleaning scene" << std::endl;
	for(auto& element : gameObjects)
	{
		if (element == nullptr)
		{
			continue;
		}
		delete element;
		element = nullptr;
	}
	for (auto& element : gameObjectsToAdd)
	{
		if (element == nullptr)
		{
			continue;
		}
		delete element;
		element = nullptr;
	}
	for (auto& element : gameObjectsToRemove)
	{
		if (element == nullptr)
		{
			continue;
		}
		delete element;
		element = nullptr;
	}
	
	gameObjects.clear();
}

void Scene::InitializeScene(sf::RenderWindow* _window)
{
	window = _window;

	mainCameraObject = CreateGameObjectImmediate("mainCameraObject");
	mainCamera = mainCameraObject->AddComponent<Camera>();
	mainCamera->Init(sf::Vector2f(1920, 1080), window, this);
	CameraManager::GetInstance()->SetMainCamera(mainCamera);
}

void Scene::RemoveGameObjectImmediate(GameObject* _gameObjectToRemove)
{
	gameObjects.RemoveElement(_gameObjectToRemove);
	delete _gameObjectToRemove;
	_gameObjectToRemove = nullptr;
}

void Scene::RemoveGameObject(GameObject* _gameObjectToAdd)
{
	gameObjectsToRemove.push_back(_gameObjectToAdd);
}


TList<GameObject*>* Scene::GetGameObjects()
{
	return &gameObjects;
}

TList<DrawableLayer*> Scene::GetDrawableLayers()
{
	TList<DrawableLayer*> drawableLayers;
	for (auto& _gameObject : gameObjects)
	{
		for (auto& _drawableComponent : *(_gameObject->GetDrawableComponents()))
		{
			drawableLayers.push_back(&_drawableComponent);
		}
	}

	return drawableLayers;
}

void Scene::CalUpdateOnAll(float deltaTime)
{
	gameObjects.AppendVector(gameObjectsToAdd);
	gameObjectsToAdd.clear();

	for (auto& _gameObject : gameObjectsToRemove)
	{
		RemoveGameObjectImmediate(_gameObject);
	}
	gameObjectsToRemove.clear();
	
	for (auto& _gameObject : gameObjects)
	{
		if (!_gameObject->GetIsActive())
		{
			continue;
		}
		for (auto& component : *_gameObject->GetComponents())
		{
			if (sceneMode == SceneMode::EditMode && component->componentWorkType == ComponentWorkType::Play)
			{
				continue;
			}
			if (sceneMode == SceneMode::PlayMode && component->componentWorkType == ComponentWorkType::Editor)
			{
				continue;
			}
			
			component->Update(deltaTime);
		}
	}
}
