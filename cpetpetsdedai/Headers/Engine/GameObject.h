#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Transformable.hpp>

#include "Object.h"

class Component;
class DrawableComponent;

enum PositionType
{
	World,
	Local,
	UI,
};

class GameObject : public Object
{
public:
	GameObject();
	GameObject(std::string _name, Type* parentType);
	AddType(GameObject, Object::GetStaticType())
	virtual void Init(std::string _name);
	std::string Name;
	
	void SetPosition(sf::Vector2f _newposition);
	void SetPosition(float _x, float _y);

	void SetScale(sf::Vector2f _newScale);
	void SetScale(float _x, float _y);


	sf::Vector2f GetPosition();
	sf::Vector2f* GetPositionPointer();
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

	PositionType positionType;
private:
	// sf::Texture* spriteTexture;
	// sf::Sprite sprite;
	
	sf::Vector2f position;
	sf::Vector2f scale;
	std::vector<std::string> _tags;
	int ZIndex;

	
	
	std::vector<Component*> components;
	std::vector<DrawableComponent*> drawableComponents;
};

