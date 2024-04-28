#include "../../Headers/Scenes/Scene.h"
#include "../../Headers/Components/Component.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Engine/GameObject.h"

Scene::Scene() : Object("Scene", Object::GetStaticType())
{
}

Scene::Scene(std::string _typeName, Type* parentType) : Object(_typeName, parentType)
{
}

std::shared_ptr<GameObject> Scene::CreateGameObject(std::string _gameObjectName, int ZIndex)
{
	std::shared_ptr<GameObject> newGameObject = std::make_shared<GameObject>();
	newGameObject->Init(_gameObjectName);
	newGameObject->SetZIndex(ZIndex);
	gameObjects.push_back(newGameObject);
	//gamesObjectsComponents[newGameObject] = std::vector<Component*>();
	return newGameObject;
}

// void Scene::AddComponent(std::shared_ptr<GameObject> _gameObject, Component* _component)
// {
// 	//gamesObjectsComponents[_gameObject].push_back(_component);
// 	_gameObject->AddComponent(_component);
// 	
// 	if (_component->GetType()->Equals(SpriteRenderer::GetStaticType()))
// 	{
// 		SpriteRenderer* spriteRenderer = dynamic_cast<SpriteRenderer*>(_component);
// 		SpriteRenderersByZIndex[spriteRenderer->GetZIndex()].push_back(spriteRenderer);
// 	}
// }

// void Scene::RemoveComponent(std::shared_ptr<GameObject> _gameObject, Component* _component)
// {
	// if (gamesObjectsComponents.contains(_gameObject))
	// {
	// 	for (int i = 0; i < gamesObjectsComponents[_gameObject].size(); i++)
	// 	{
	// 		if (gamesObjectsComponents[_gameObject][i] == _component)
	// 		{
	// 			gamesObjectsComponents[_gameObject].erase(gamesObjectsComponents[_gameObject].begin() + i);
	// 			return;
	// 		}
	// 		gamesObjectsComponents.erase(_gameObject);
	// 	}
	// }
// 	_gameObject->RemoveComponent(_component);
// }


void Scene::InitializeScene(sf::RenderWindow* _window)
{
	window = _window;

	mainCameraObject = CreateGameObject("mainCameraObject", 0);
	mainCamera = mainCameraObject->AddComponent<Camera>(sf::Vector2f(10000, 10000), window, this);
	
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> _gameObjectToRemove)
{
	//gamesObjectsComponents.erase(_gameObjectToRemove);
}

std::vector<std::shared_ptr<GameObject>>* Scene::GetGameObjects()
{
	return &gameObjects;
}

std::map<int, std::vector<SpriteRenderer*>>* Scene::GetSpriteRenderersByZIndex()
{
	return &SpriteRenderersByZIndex;
}

void Scene::CalUpdateOnAll(float deltaTime)
{
	for (auto& _gameObject : gameObjects)
	{
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
