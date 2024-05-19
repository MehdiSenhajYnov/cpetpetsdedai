#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Headers/Engine/Object.h"

class DrawableLayer;
class DrawableComponent;

// SINGLETON
class RendererManager : public Object{
public:
	void Init(sf::RenderWindow* _window);
	void Clear();
	void DrawProcess();

	void DrawEngineUI();
	void CustomDraw(const sf::Drawable* _drawable) const;
	
	void AddDrawableLayer(DrawableComponent* _drawableComponent);
	static RendererManager* GetInstance();
	static void ResetInstance();
	bool isOnDisplay(DrawableComponent* toCheck);

	sf::RenderWindow* GetWindow() const;

	TList<DrawableLayer>& GetDrawableLayers();

private:
	RendererManager() = default;
	sf::RenderWindow* window;
	TList<DrawableLayer> drawableLayers;
	static RendererManager* instance;

	std::vector<sf::CircleShape> fordebug;
};
