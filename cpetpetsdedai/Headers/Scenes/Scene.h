#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "../Components/Camera.h"
#include "../Components/SpriteRenderer.h"

class GameObject;
class Component;

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
	virtual ~Scene() = default;

	virtual void InitializeScene(sf::RenderWindow* _window);
	
	void RemoveGameObject(std::shared_ptr<GameObject> _gameObjectToAdd);
	std::string sceneName;
	std::shared_ptr<GameObject> CreateGameObject(std::string _gameObjectName, int ZIndex);

	std::vector<std::shared_ptr<GameObject>>* GetGameObjects();
	std::map<int, std::vector<SpriteRenderer*>>* GetSpriteRenderersByZIndex();

	//void AddComponent(std::shared_ptr<GameObject> _gameObject, Component* _component);
	//void RemoveComponent(std::shared_ptr<GameObject> _gameObject, Component* _component);

	void CalUpdateOnAll(float deltaTime);
	virtual void Update(float deltaTime) = 0;

	virtual void OnKeyDown(sf::Keyboard::Key pressedKey) = 0;

	virtual void DestroyScene() = 0;
	SceneMode sceneMode = SceneMode::PlayMode;

	std::shared_ptr<GameObject> mainCameraObject;
	Camera mainCamera;
	
protected:

	bool sceneChanged;

	sf::RenderWindow* window;
	
	std::vector<std::shared_ptr<GameObject>> gameObjects;
	std::map<int, std::vector<SpriteRenderer*>> SpriteRenderersByZIndex;
};

