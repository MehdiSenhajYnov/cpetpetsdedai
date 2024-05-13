#pragma once
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "Component.h"

class Camera : public Component
{
public:
	Camera();
	void AddToPermanentDrawablesObjects(sf::Shape* drawableToAdd, GameObject* attachedObject);
	void RemoveFromPermanentDrawablesObjects(sf::Shape* drawableToRemove);

	void AddToTexts(sf::Text* textToAdd);
	void RemoveFromTexts(sf::Text* textToRemove);

	sf::RenderWindow* GetCurrentWindow();
	void UpdateCameraRect();

	void Init(sf::Vector2f _cameraView, sf::RenderWindow* _window);
	sf::FloatRect GetCameraRect();

private:
	std::vector<sf::Text*> Texts;
	std::map <sf::Shape*, GameObject*> PermanentDrawablesObjects;
	sf::Vector2f CameraView;
	sf::RenderWindow* window;

	sf::FloatRect CameraRect;
	
	void Start() override;
	void Update(float deltaTime) override;

};

