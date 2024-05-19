#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>

#include "Object.h"
#include "../../DrawableLayer.h"
#include "../../Factory.h"
#include "../Components/Component.h"
#include "../Engine/Field.h"

#define SameTypeOfT() \
[](Component* component) { return component->GetType()->Equals(T::GetStaticType()); }

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
	GameObject(const std::string& _name, Type* parentType);

	~GameObject() override;
	ADD_TYPE(GameObject, Object, REG_TYPE)
	
	virtual void Init(const std::string& _name);

	
	#pragma region GettersSetters

	void ComponentsManagement();
	
	std::string GetName();
	void SetName(const std::string& _name);
		
	TList<std::string> GetTags();
	void AddTags(const std::string& _tagToAdd);
	void RemoveTags(const std::string& _tagToRemove);

	GameObject* GetParent() const;
	void SetParent(GameObject* _parent);

	bool GetIsActive() const;
	void SetIsActive(bool is_active);

	#pragma endregion GettersSetters
	
	#pragma region TransformManagement

	void SetPosition(const sf::Vector2f& _newposition);
	void SetPosition(float _x, float _y);
	void SetScale(const sf::Vector2f& _newScale);
	void SetScale(const float& _x, const float& _y);
	
	sf::Vector2f GetPosition() const;
	sf::Vector2f* GetPositionPointer();
	
	void Move(const float& _x, const float& _y);
	void Move(sf::Vector2f _moveBy);

	sf::Vector2f GetScale() const;

	#pragma endregion TransformManagement

	#pragma region ComponentsManagement

	TList<Component*>& GetComponents();

	template <typename T, typename... Args>
	T* AddComponent(Args... args) requires IsBaseOf<Component, T>;

	template <typename T>
	T* AddComponent() requires IsBaseOf<Component, T>; 

	Component* AddComponentByName(const std::string& _typeName);
	
	template <typename T>
	void RemoveComponent() requires IsBaseOf<Component, T>;

	template <typename T>
	int RemoveAllComponents() requires IsBaseOf<Component, T>;

	template <typename T>
	Component* GetComponent() requires IsBaseOf<Component, T>;

	template <typename T>
	TList<Component*> GetAllComponents() requires IsBaseOf<Component, T>;
	#pragma endregion ComponentsManagement

public:
	PositionType positionType = PositionType::World;
private:
	std::string name = "";
	sf::Vector2f position = {0, 0};
	sf::Vector2f scale = {1, 1};
	TList<std::string> _tags;

	TList<Component*> componentsToAdd;
	TList<Component*> componentsToRemove;
	TList<Component*> components;
	GameObject* parent = nullptr;

	bool isActive = true;
	
};

template <typename T, typename... Args>
T* GameObject::AddComponent(Args... args) requires IsBaseOf<Component, T>
{
	T* newComponent = Factory::GetInstance()->CreateObject<T>();
	newComponent->InitBaseComponent(this);
	newComponent->Init(std::forward<Args>(args)...);
	newComponent->Start();
	//components.push_back(newComponent);
	componentsToAdd.push_back(newComponent);
	return newComponent;
}

template <typename T>
T* GameObject::AddComponent() requires IsBaseOf<Component, T>
{
	T* newComponent = Factory::GetInstance()->CreateObject<T>();
	newComponent->InitBaseComponent(this);
	newComponent->Start();
	//components.push_back(newComponent);
	componentsToAdd.push_back(newComponent);
	return newComponent;
}

template <typename T>
void GameObject::RemoveComponent() requires IsBaseOf<Component, T>
{
	Component* toDelete = GetComponent<T>();
	componentsToRemove.push_back(toDelete);
	//components.RemoveElement(toDelete);
	//Factory::GetInstance()->DestroyObject(toDelete);;
}

template <typename T>
int GameObject::RemoveAllComponents() requires IsBaseOf<Component, T>
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
Component* GameObject::GetComponent() requires IsBaseOf<Component, T>
{
	return components.GetFirstWith(SameTypeOfT());
}

template <typename T>
TList<Component*> GameObject::GetAllComponents() requires IsBaseOf<Component, T>
{
	return components.GetAllWith(SameTypeOfT());
}
