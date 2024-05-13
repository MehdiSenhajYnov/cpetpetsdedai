#include "../../Headers/Scenes/Scene.h"
#include "../../CameraManager.h"
#include "../../EngineUI.h"
#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/Component.h"
#include "../../Headers/Engine/GameObject.h"

Scene::Scene() : Scene("Scene", Object::GetStaticType())
{
}

Scene::Scene(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType)
{
	sceneFileEditor.SetCurrentScene(this);
}

GameObject* Scene::CreateGameObject(const std::string& _gameObjectName)
{
	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>();
	newGameObject->Init(_gameObjectName);
	gameObjectsToAdd.push_back(newGameObject);
	return newGameObject;
}

GameObject* Scene::CreateGameObjectImmediate(const std::string& _gameObjectName)
{
	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>();
	newGameObject->Init(_gameObjectName);
	gameObjects.push_back(newGameObject);
	//gamesObjectsComponents[newGameObject] = std::vector<Component*>();
	return newGameObject;
}



void Scene::InitializeScene(sf::RenderWindow* _window)
{
	window = _window;

	mainCameraObject = CreateGameObjectImmediate("mainCameraObject");
	mainCamera = mainCameraObject->AddComponent<Camera>();
	mainCamera->Init(sf::Vector2f(1920, 1080), window);
	CameraManager::GetInstance()->SetMainCamera(mainCamera);
}

void Scene::RemoveGameObjectImmediate(GameObject* _gameObjectToRemove)
{
	gameObjects.RemoveElement(_gameObjectToRemove);
	Factory::GetInstance()->DestroyObject(_gameObjectToRemove);
}

void Scene::RemoveGameObject(GameObject* _gameObjectToAdd)
{
	gameObjectsToRemove.push_back(_gameObjectToAdd);
}


TList<GameObject*>& Scene::GetGameObjects()
{
	return gameObjects;
}

TList<DrawableLayer*> Scene::GetDrawableLayers() const
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

void Scene::BaseSceneUpdate(float deltaTime)
{
	UpdatePreComponent(deltaTime);
	
	// TODO : Change the position of this loop
	for (auto& _uiElement : EngineUI::GetInstance()->GetUIElements())
	{
		if (_uiElement == nullptr) continue;
		if (!_uiElement->IsInitialized()) continue;
		_uiElement->Update(deltaTime);
	}
	
	
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

	UpdatePostComponent(deltaTime);
}

void Scene::OnKeyDown(sf::Keyboard::Key pressedKey)
{
	for (auto& _uiElement : EngineUI::GetInstance()->GetUIElements())
	{
		if (_uiElement == nullptr) continue;
		_uiElement->OnKeyDown(pressedKey);
	}
	
}

void Scene::OnMouseKeyDown(sf::Mouse::Button pressedKey)
{
	for (auto& _uiElement : EngineUI::GetInstance()->GetUIElements())
	{
		if (_uiElement == nullptr) continue;
		_uiElement->OnMouseKeyDown(pressedKey);
	}
}

void Scene::OnMouseKeyUp(sf::Mouse::Button pressedKey)
{
	for (auto& _uiElement : EngineUI::GetInstance()->GetUIElements())
	{
		if (_uiElement == nullptr) continue;
		_uiElement->OnMouseKeyUp(pressedKey);
	}
}



void Scene::ClearAll()
{
	for(auto& element : gameObjects)
	{
		Factory::GetInstance()->DestroyObject(element);
	}
	gameObjects.clear();

	for (auto& element : gameObjectsToAdd)
	{
		Factory::GetInstance()->DestroyObject(element);
	}
	gameObjectsToAdd.clear();
	
	for (auto& element : gameObjectsToRemove)
	{
		Factory::GetInstance()->DestroyObject(element);
	}
	gameObjectsToRemove.clear();
}

void Scene::PreDestroy()
{
	sceneFileEditor.SaveScene();
	ClearAll();
	DestroyScene();
}

Scene::~Scene()
{
	ClearAll();
	
}