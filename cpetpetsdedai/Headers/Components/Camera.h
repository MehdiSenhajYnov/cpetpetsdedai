#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"
#include "EditorComponent.h"

class Scene;

class Camera : public EditorComponent
{
public:
	Camera();
	void Render();
	bool IsOnDisplay(GameObject* toCheck);
	void AddToPermanentDrawablesObjects(sf::Shape* drawableToAdd, std::shared_ptr<GameObject> attachedObject);
	void RemoveFromPermanentDrawablesObjects(sf::Shape* drawableToRemove);

	void AddToTexts(sf::Text* textToAdd);
	void RemoveFromTexts(sf::Text* textToRemove);

	sf::RenderWindow* GetCurrentWindow();


	void Initialize(std::shared_ptr<GameObject> _gameObject, sf::Vector2<float> _cameraView, sf::RenderWindow* _window, Scene* _scene);
private:
	std::vector<sf::Text*> Texts;
	std::map <sf::Shape*, std::shared_ptr<GameObject>> PermanentDrawablesObjects;
	sf::Vector2<float> CameraView;
	sf::RenderWindow* window;
	Scene* scene;

	void Start() override;
	void Update(float deltaTime) override;

};

