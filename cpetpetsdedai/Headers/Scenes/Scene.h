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
	ADD_TYPE(Scene, Object, REG_TYPE)
	virtual ~Scene() override;

	void ClearAll();
	virtual void PreDestroy() override;

	void BaseInit(sf::RenderWindow* _window);
	virtual void InitializeScene(sf::RenderWindow* _window);
	sf::RenderWindow* GetWindow() const;

	std::string sceneName;

	virtual void AddMethods() {};
	
	// GameObject* CreateGameObject(const std::string& _gameObjectName);
	// GameObject* CreateGameObject(const std::string& _gameObjectName, uint64_t _id);
	// GameObject* CreateGameObject(uint64_t _id);
	//
	//
	// GameObject* CreateGameObjectImmediate(const std::string& _gameObjectName);
	// GameObject* CreateGameObjectImmediate(const std::string& _gameObjectName, uint64_t _id);
	// GameObject* CreateGameObjectImmediate(uint64_t _id);

	// template<typename T>
	// T* CreateGameObjectImmediate(std::string _gameObjectName) requires IsDerivedFrom<T, GameObject>
	// {
	// 	T* newGameObject = Factory::GetInstance()->CreateObject<T>();
	// 	newGameObject->Init(_gameObjectName);
	// 	gameObjects.push_back(newGameObject);
	// 	return newGameObject;
	// }

	void RemoveGameObjectImmediate(GameObject* _gameObjectToRemove);
	void RemoveGameObject(GameObject* _gameObjectToAdd);
	
	TList<GameObject*>& GetGameObjects();
	
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
	
	SceneFileEditor sceneFileEditor = SceneFileEditor();
protected:
	void OnObjectCreated(Object* _object);
	bool sceneChanged = false;

	sf::RenderWindow* window = nullptr;
	
	TList<GameObject*> gameObjects;
	
	TList<GameObject*> gameObjectsToAdd;
	TList<GameObject*> gameObjectsToRemove;
	int eventID = -1;
};

