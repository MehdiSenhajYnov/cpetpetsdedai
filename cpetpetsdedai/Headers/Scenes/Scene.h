#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SceneFileEditor.h"
#include "../Engine/Object.h"

class DrawableLayer;
class GameObject;
class Component;
class SpriteRenderer;
class Camera;

enum SceneMode
{
	PlayMode,
	EditMode
};

class Scene : public Object
{
public:
	Scene();
	Scene(const std::string& _typeName, Type* parentType);
	AddType(Scene, Object)
	virtual ~Scene() override;

	void ClearAll();
	virtual void PreDestroy() override;
	
	virtual void InitializeScene(sf::RenderWindow* _window);
	
	std::string sceneName;
	
	GameObject* CreateGameObject(const std::string& _gameObjectName);
	GameObject* CreateGameObjectImmediate(const std::string& _gameObjectName);

	template<typename T>
	T* CreateGameObjectImmediate(std::string _gameObjectName) requires IsDerivedFrom<T, GameObject>
	{
		T* newGameObject = Factory::GetInstance()->CreateObject<T>();
		newGameObject->Init(_gameObjectName);
		gameObjects.push_back(newGameObject);
		return newGameObject;
	}

	void RemoveGameObjectImmediate(GameObject* _gameObjectToRemove);
	void RemoveGameObject(GameObject* _gameObjectToAdd);
	
	TList<GameObject*>& GetGameObjects();
	TList<DrawableLayer*> GetDrawableLayers() const;
	
	void BaseSceneUpdate(float deltaTime);
	virtual void UpdatePreComponent(float deltaTime) {}
	virtual void UpdatePostComponent(float deltaTime) {}
	
	virtual void OnKeyDown(sf::Keyboard::Key pressedKey);
	virtual void OnMouseKeyDown(sf::Mouse::Button pressedKey);
	virtual void OnMouseKeyUp(sf::Mouse::Button pressedKey);

	virtual void DestroyScene() = 0;
	SceneMode sceneMode = SceneMode::PlayMode;

	GameObject* mainCameraObject = nullptr;
	Camera* mainCamera = nullptr;
	
	SceneFileEditor sceneFileEditor;
protected:
	bool sceneChanged = false;

	sf::RenderWindow* window = nullptr;
	
	TList<GameObject*> gameObjects;
	
	TList<GameObject*> gameObjectsToAdd;
	TList<GameObject*> gameObjectsToRemove;
};

