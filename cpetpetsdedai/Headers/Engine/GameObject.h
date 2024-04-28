#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"
#include "../../TList.h"

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
	~GameObject() override;
	
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
	void AddTags(const std::string& _tagToAdd);
	void RemoveTags(const std::string& _tagToAdd);

	int GetZIndex();
	void SetZIndex(int _zIndex);

	//void AddComponent(Component* _component);
	//void RemoveComponent(Component* _component);
	
	std::vector<Component*>* GetComponents();

	void AddDrawableComponent(DrawableComponent* _drawableComponent);
	void RemoveDrawableComponent(DrawableComponent* _drawableComponent);
	std::vector<DrawableComponent*>* GetDrawableComponents();
	
	PositionType positionType;

	template <typename T, typename... Args>
	T* AddComponent(Args... args);

	template <typename T>
	T* AddComponent();
	
	template <typename T>
	bool RemoveComponent();

	template <typename T>
	int RemoveAllComponents();

	template <typename T>
	Component* GetComponent();

	template <typename T>
	TList<Component*> GetAllComponents();
	
private:
	sf::Vector2f position;
	sf::Vector2f scale;
	std::vector<std::string> _tags;
	int ZIndex;
	
	TList<Component*> components;
	//TList<Component*> componentsToDelete;
	
	std::vector<DrawableComponent*> drawableComponents;
};

