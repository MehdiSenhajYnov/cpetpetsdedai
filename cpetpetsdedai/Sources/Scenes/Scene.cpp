#include "../../Headers/Scenes/Scene.h"

#include "../../EditorCameraUserMove.h"
#include "../../EngineUI.h"
#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/Component.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/PhysicsEngine.h"

Scene::Scene() : Scene("Scene", Object::GetStaticType())
{
}

Scene::Scene(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType)
{
	sceneFileEditor.SetCurrentScene(this);
}
//
// GameObject* Scene::CreateGameObject(const std::string& _gameObjectName)
// {
// 	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>();
// 	newGameObject->Init(_gameObjectName);
// 	gameObjectsToAdd.push_back(newGameObject);
// 	return newGameObject;
// }
//
// GameObject* Scene::CreateGameObject(const std::string& _gameObjectName, uint64_t _id)
// {
// 	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>(_id);
// 	newGameObject->Init(_gameObjectName);
// 	gameObjectsToAdd.push_back(newGameObject);
// 	return newGameObject;
// }
//
// GameObject* Scene::CreateGameObject(uint64_t _id)
// {
// 	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>(_id);
// 	gameObjectsToAdd.push_back(newGameObject);
// 	return newGameObject;
// }
//
// GameObject* Scene::CreateGameObjectImmediate(const std::string& _gameObjectName)
// {
// 	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>();
// 	newGameObject->Init(_gameObjectName);
// 	gameObjects.push_back(newGameObject);
// 	return newGameObject;
// }
//
// GameObject* Scene::CreateGameObjectImmediate(const std::string& _gameObjectName, uint64_t _id)
// {
// 	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>(_id);
// 	newGameObject->Init(_gameObjectName);
// 	gameObjects.push_back(newGameObject);
// 	return newGameObject;
// }
//
// GameObject* Scene::CreateGameObjectImmediate(uint64_t _id)
// {
// 	GameObject* newGameObject = Factory::GetInstance()->CreateObject<GameObject>(_id);
// 	gameObjects.push_back(newGameObject);
// 	return newGameObject;
// }

void Scene::BaseInit(sf::RenderWindow* _window)
{
	window = _window;
	eventID = Factory::GetInstance()->OnGameObjectCreated.Subscribe(&Scene::OnObjectCreated, this);
}
void Scene::InitializeScene(sf::RenderWindow* _window)
{
	// window = _window;
	// eventID = Factory::GetInstance()->OnGameObjectCreated.Subscribe(&Scene::OnObjectCreated, this);

	
	mainCameraObject = Create<GameObject>();
	mainCameraObject->Init("mainCameraObject");
	mainCamera = mainCameraObject->AddComponent<Camera>();
	mainCamera->Init(sf::Vector2f(1920, 1080));
	
	mainCameraObject->AddComponent<EditorCameraUserMove>();
	
}

sf::RenderWindow* Scene::GetWindow() const
{
	return window;
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

void Scene::BaseSceneUpdate(float deltaTime)
{
	
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

	UpdatePreComponent(deltaTime);

	
	for (int i = 0; i < gameObjects.size(); ++i)
	{
		auto _gameObject = gameObjects[i];
		if (_gameObject == nullptr) continue;
		
		_gameObject->ComponentsManagement();
		if (!_gameObject->GetIsActive())
		{
			continue;
		}
		for (int j = 0; j < _gameObject->GetComponents().size(); ++j)
		{
			auto component = _gameObject->GetComponents()[j];

			if (sceneMode == SceneMode::EditMode && component->componentWorkType == ComponentWorkType::PlayOnly)
			{
				continue;
			}
			if (sceneMode == SceneMode::PlayMode && component->componentWorkType == ComponentWorkType::EditorOnly)
			{
				continue;
			}
			
			component->Update(deltaTime);
		}
	}

	if (sceneMode == SceneMode::PlayMode)
	{
		PhysicsEngine::GetInstance()->UpdatePhysics(deltaTime);
	}

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		auto _gameObject = gameObjects[i];
		if (!_gameObject->GetIsActive())
		{
			continue;
		}
		for (int j = 0; j < _gameObject->GetComponents().size(); ++j)
		{
			auto component = _gameObject->GetComponents()[j];

			if (sceneMode == SceneMode::EditMode && component->componentWorkType == ComponentWorkType::PlayOnly)
			{
				continue;
			}
			if (sceneMode == SceneMode::PlayMode && component->componentWorkType == ComponentWorkType::EditorOnly)
			{
				continue;
			}
			
			component->LateUpdate(deltaTime);
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

void Scene::OnObjectCreated(Object* _object)
{
	
	if (Type::IsOrIsDescendantOf(_object->GetType(), GameObject::GetStaticType()))
	{
		gameObjectsToAdd.push_back(dynamic_cast<GameObject*>(_object));
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
	Factory::GetInstance()->OnGameObjectCreated.Unsubscribe(eventID);
	ClearAll();
	
}
