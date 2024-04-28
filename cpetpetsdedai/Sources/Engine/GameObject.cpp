#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/TextureManager.h"
#include "../../Headers/Components/Component.h"
#include "../../Headers/Utilities/Utilities.h"

#define SameTypeOfT() \
[](Component* component) { return component->GetType()->Equals(T::GetStaticType()); }

GameObject::GameObject(): Object("GameObject", Object::GetStaticType()), positionType(World), ZIndex(0)
{
}

GameObject::GameObject(std::string _name, Type* parentType) : Object(_name, parentType), positionType(World), ZIndex(0)
{
}

GameObject::~GameObject()
{
	for (auto& _componentToDelete : components)
	{
		delete _componentToDelete;
		_componentToDelete = nullptr;
	}
}

void GameObject::Init(std::string _name)
{
	Name = _name;
}

void GameObject::SetPosition(sf::Vector2f _newposition)
{
	position = _newposition;
}

void GameObject::SetPosition(float _x, float _y)
{
	position = sf::Vector2f(_x, _y);
}

void GameObject::SetScale(sf::Vector2f _newScale)
{
	scale = _newScale;
}

void GameObject::SetScale(float _x, float _y)
{
	scale = sf::Vector2f(_x, _y);
}


// void GameObject::SetColor(sf::Color _color)
// {
// 	sprite.setColor(_color);
// }
//
// sf::Color GameObject::GetColor()
// {
// 	return sprite.getColor();
// }

sf::Vector2f GameObject::GetPosition()
{
	return position;
}


sf::Vector2f* GameObject::GetPositionPointer()
{
	return &position;
}

void GameObject::Move(float _x, float _y)
{
	if (position.x + _x >= std::numeric_limits<float>::max() || position.y + _y >= std::numeric_limits<float>::max())
	{
		std::cout << "out of limit MAX position" << '\n';
		return;
	}
	if (position.x + _x <= std::numeric_limits<float>::min() || position.y + _y <= std::numeric_limits<float>::min())
	{
		std::cout << "out of limit MIN position" << '\n';
		return;
	}

	SetPosition(GetPosition().x + _x, GetPosition().y + _y);
}

void GameObject::Move(sf::Vector2f _moveBy)
{
	if ((position + _moveBy).x >= std::numeric_limits<float>::max() || (position + _moveBy).y >= std::numeric_limits<float>::max())
	{
		std::cout << "out of limit MAX position" << '\n';
		return;
	}
	if ((position + _moveBy).x <= -std::numeric_limits<float>::max() || (position + _moveBy).y <= -std::numeric_limits<float>::max())
	{
		std::cout << "out of limit MIN position" << '\n';
		return;
	}

	SetPosition(GetPosition() + _moveBy);
}

std::vector<std::string> GameObject::GetTags()
{
	return _tags;
}

void GameObject::AddTags(const std::string& _tagToAdd)
{
	_tags.push_back(_tagToAdd);
}

void GameObject::RemoveTags(const std::string& _tagToRemove)
{
	for (int i = 0; i < _tags.size(); i++)
	{
		if (_tags[i] == _tagToRemove)
		{
			_tags.erase(_tags.begin() + i);
			return;
		}
	}
}

int GameObject::GetZIndex()
{
	return ZIndex;
}

void GameObject::SetZIndex(int _zIndex)
{
	ZIndex = _zIndex;
}

std::vector<Component*>* GameObject::GetComponents()
{
	return &components;
}

void GameObject::AddDrawableComponent(DrawableComponent* _drawableComponent)
{
	drawableComponents.push_back(_drawableComponent);
}

void GameObject::RemoveDrawableComponent(DrawableComponent* _drawableComponent)
{
	for (int i = 0; i < drawableComponents.size(); i++)
	{
		if (drawableComponents[i] == _drawableComponent)
		{
			drawableComponents.erase(drawableComponents.begin() + i);
			return;
		}
	}
}

std::vector<DrawableComponent*>* GameObject::GetDrawableComponents()
{
	return &drawableComponents;
}



template <typename T, typename... Args>
T* GameObject::AddComponent(Args... args)
{
	T* newComponent = new T();
	
	newComponent->InitBaseComponent(this);
	newComponent->Init(std::forward<Args>(args)...);
	components.push_back(newComponent);
	//componentsToDelete.push_back(newComponent);
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
