#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Object.h"
#include "../../TList.h"
#include "../Components/Component.h"

#define SameTypeOfT() \
[](Component* component) { return component->GetType()->Equals(T::GetStaticType()); }

class DrawableComponent;

struct DrawableLayer
{
	int ZIndex;	
	TList<DrawableComponent*> drawableComponents;

	DrawableComponent* operator[](const int& index) {
		return drawableComponents[index];
	}
	const DrawableComponent* operator[](const int& index) const {
		return drawableComponents[index];
	}
};

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

	sf::Vector2f GetScale();
	
	TList<std::string> GetTags();
	void AddTags(const std::string& _tagToAdd);
	void RemoveTags(const std::string& _tagToAdd);

	TList<Component*>* GetComponents();

	void AddDrawableComponent(DrawableComponent* _drawableComponent);
	void RemoveDrawableComponent(DrawableComponent* _drawableComponent);
	
	TList<DrawableLayer>* GetDrawableComponents();
	
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
	TList<std::string> _tags;
	
	TList<Component*> components;
	GameObject* parent;

public:
	GameObject* GetParent() const;
	void SetParent(GameObject* _parent);

private:
	TList<DrawableLayer> drawableComponents;
	bool isActive;

public:
	bool GetIsActive() const;
	void SetIsActive(bool is_active);
};

template <typename T, typename... Args>
T* GameObject::AddComponent(Args... args)
{
	T* newComponent = new T();
	newComponent->InitBaseComponent(this);
	newComponent->Init(std::forward<Args>(args)...);
	components.push_back(newComponent);
	return newComponent;
}

template <typename T>
T* GameObject::AddComponent()
{
	T* newComponent = new T();
	newComponent->InitBaseComponent(this);
	components.push_back(newComponent);
	return newComponent;
}

template <typename T>
bool GameObject::RemoveComponent()
{
	Component* deletedComponent = nullptr;
	components.RemoveFirstWith(SameTypeOfT(), deletedComponent);
	if (deletedComponent != nullptr) {
		delete deletedComponent;
		deletedComponent = nullptr;
		return true;
	}
	return false;
}

template <typename T>
int GameObject::RemoveAllComponents()
{
	int count = 0;
	bool result = RemoveComponent<T>();
	while (result) {
		count++;
		result = RemoveComponent<T>();
	}
	return count;
}

template <typename T>
Component* GameObject::GetComponent()
{
	return components.GetFirstWith(SameTypeOfT());
}

template <typename T>
TList<Component*> GameObject::GetAllComponents()
{
	return components.GetAllWith(SameTypeOfT());
}
