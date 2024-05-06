#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>

#include "Object.h"
#include "../Components/Component.h"
#include "../Engine/Field.h"

#define SameTypeOfT() \
[](Component* component) { return component->GetType()->Equals(T::GetStaticType()); }

class DrawableComponent;

struct DrawableLayer
{
public:
	// friend std::ostream& operator<<(std::ostream& _os, const DrawableLayer& _obj)
	// {
	// 	return _os
	// 		<< "ZIndex: " << _obj.ZIndex
	// 		<< " drawableComponents: " << _obj.drawableComponents;
	// }

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
	GameObject(const std::string& _name, Type* parentType);
	~GameObject() override;
	
	static Type* GetStaticType()
	{
		static Type _objtype("GameObject", Object::GetStaticType());
		return &_objtype;
	}
	virtual void Init(const std::string& _name);

	#pragma region GettersSetters
	
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

	TList<Component*>* GetComponents();

	void AddDrawableComponent(DrawableComponent* _drawableComponent);
	void RemoveDrawableComponent(DrawableComponent* _drawableComponent);
	
	TList<DrawableLayer>* GetDrawableComponents();
	
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
	#pragma endregion ComponentsManagement

	
	static void SerializeClass()
	{

		std::vector<BaseField*> fields;
		
		Field<int*> test = Field<int*>();
		fields.push_back(&test);

	}
	
	// template <typename T>
	// static void SerializeField(std::string _fieldName)
	// {
	// 	Field field = Field<T>() ;
	// 	field.name = _fieldName;
	// }

	static void AddField(BaseField* _field)
	{
		static std::map<std::string, BaseField*> fields;
		fields[_field->name] = _field;
	}
	
public:
	PositionType positionType;
private:
	std::string name;
	sf::Vector2f position;
	sf::Vector2f scale;
	TList<std::string> _tags;
	
	TList<Component*> components;
	GameObject* parent;

	TList<DrawableLayer> drawableComponents;
	bool isActive = false;
	
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
