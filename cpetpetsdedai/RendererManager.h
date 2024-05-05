#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TList.h"

class DrawableComponent;
struct DrawableLayer;

class RendererManager {
public:
	void Init(sf::RenderWindow* _window);
	void Clear();
	void Draw();
	void AddDrawableLayer(DrawableComponent* _drawableComponent);
	static RendererManager* GetInstance();
	static void ResetInstance();
	bool isOnDisplay(DrawableComponent* toCheck);

private:
	RendererManager() = default;
	sf::RenderWindow* window;
	TList<DrawableLayer> drawableLayers;
	static RendererManager* instance;

	std::vector<sf::CircleShape> fordebug;
};
