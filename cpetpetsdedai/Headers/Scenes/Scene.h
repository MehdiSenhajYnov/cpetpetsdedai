#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "../../TList.h"
#include "../Engine/Object.h"

struct DrawableLayer;
class GameObject;
class Component;
class SpriteRenderer;
class Camera;

enum SceneMode
{
	PlayMode,
	EditMode
};

class Scene : Object
{
public:
	Scene();
	Scene(std::string _typeName, Type* parentType);
	AddType(Scene, Object::GetStaticType());
	virtual ~Scene();

	virtual void InitializeScene(sf::RenderWindow* _window);
	
	void RemoveGameObject(GameObject* _gameObjectToAdd);
	std::string sceneName;
	GameObject* CreateGameObject(std::string _gameObjectName);

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
	
protected:

	bool sceneChanged;

	sf::RenderWindow* window;
	
	TList<GameObject*> gameObjects;
};

