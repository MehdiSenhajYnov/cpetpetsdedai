#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Transformable.hpp>

#include "Object.h"

class Component;
class DrawableComponent;

class GameObject : public Object
{
public:
	GameObject();
	AddType(GameObject, Object::GetStaticType());
	void InitGameObject(std::string _name);
	std::string Name;
	
	// sf::Sprite* GetSprite();
	// void SetSprite(const std::string& _spriteName);
	//
	// void SetSprite(const std::string& _spriteName, sf::IntRect textureRect);
	// void SetTexture(sf::Texture* _texture);
	// void SetColor(sf::Color _color);
	// sf::Color GetColor();

	void SetPosition(sf::Vector2<float> _newposition);
	void SetPosition(float _x, float _y);

	void SetScale(sf::Vector2<float> _newScale);
	void SetScale(float _x, float _y);


	sf::Vector2<float> GetPosition();
	sf::Vector2<float>* GetPositionPointer();
	void Move(float _x, float _y);
	void Move(sf::Vector2f _moveBy);

	std::vector<std::string> GetTags();
	void AddTags(std::string tagToAdd);
	void RemoveTags(std::string tagToAdd);

	int GetZIndex();
	void SetZIndex(int _zIndex);

	void AddComponent(Component* _component);
	void RemoveComponent(Component* _component);
	
	std::vector<Component*>* GetComponents();

	void AddDrawableComponent(DrawableComponent* _drawableComponent);
	void RemoveDrawableComponent(DrawableComponent* _drawableComponent);
	std::vector<DrawableComponent*>* GetDrawableComponents();
	
private:
	// sf::Texture* spriteTexture;
	// sf::Sprite sprite;
	
	sf::Vector2<float> position;
	sf::Vector2<float> scale;
	std::vector<std::string> _tags;
	int ZIndex;
	
	std::vector<Component*> components;
	std::vector<DrawableComponent*> drawableComponents;
};

