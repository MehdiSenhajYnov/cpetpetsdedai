#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "SceneFileEditor.h"
#include "../../TList.h"
#include "../Engine/GameObject.h"
#include "../Engine/Object.h"

struct DrawableLayer;
class GameObject;
class Component;
class SpriteRenderer;
class Camera;

template<typename T>
concept isGameObject =
	std::is_base_of_v<GameObject, T> &&
	std::is_convertible_v<const volatile T*, const volatile GameObject*>;

enum SceneMode
{
	PlayMode,
	EditMode
};

class Scene : public Object
{
public:
	Scene();
	Scene(std::string _typeName, Type* parentType);
	AddType(Scene, Object::GetStaticType());
	virtual ~Scene();

	virtual void InitializeScene(sf::RenderWindow* _window);
	
	std::string sceneName;
	
	GameObject* CreateGameObject(std::string _gameObjectName);
	GameObject* CreateGameObjectImmediate(std::string _gameObjectName);

	template<isGameObject T>
	T* CreateGameObjectImmediate(std::string _gameObjectName)
	{
		T* newGameObject = new T();
		newGameObject->Init(_gameObjectName);
		gameObjects.push_back(newGameObject);
		return newGameObject;
	}

	void RemoveGameObjectImmediate(GameObject* _gameObjectToAdd);
	void RemoveGameObject(GameObject* _gameObjectToAdd);
	

	TList<GameObject*>* GetGameObjects();
	TList<DrawableLayer*> GetDrawableLayers();
	
	void CalUpdateOnAll(float deltaTime);
	virtual void Update(float deltaTime) = 0;

	virtual void OnKeyDown(sf::Keyboard::Key pressedKey) {};
	virtual void OnMouseKeyDown(sf::Mouse::Button pressedKey) {};

	virtual void DestroyScene() = 0;
	SceneMode sceneMode = SceneMode::PlayMode;

	GameObject* mainCameraObject;
	Camera* mainCamera;
	
	SceneFileEditor sceneFileEditor;
protected:
	bool sceneChanged;

	sf::RenderWindow* window;
	
	TList<GameObject*> gameObjects;
	
	TList<GameObject*> gameObjectsToAdd;
	TList<GameObject*> gameObjectsToRemove;
};

