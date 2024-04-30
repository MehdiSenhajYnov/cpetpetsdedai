#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/TextureManager.h"
#include "../../Headers/Components/Component.h"
#include "../../Headers/Components/DrawableComponent.h"
#include "../../Headers/Utilities/Utilities.h"

GameObject::GameObject(): GameObject("GameObject", Object::GetStaticType())
{
	
}

GameObject::GameObject(std::string _name, Type* parentType) : Object(_name, parentType), positionType(World)
{
	scale = sf::Vector2f(1, 1);
	position = sf::Vector2f(0, 0);
	isActive = true;
	parent = nullptr;
}

GameObject::~GameObject()
{
	for (auto& _componentToDelete : components)
	{
		_componentToDelete->PreDestroy();
		delete _componentToDelete;
		_componentToDelete = nullptr;
	}
	components.clear();
	drawableComponents.clear();
	_tags.clear();
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

sf::Vector2f GameObject::GetScale()
{
	return scale;
}

TList<std::string> GameObject::GetTags()
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


TList<Component*>* GameObject::GetComponents()
{
	return &components;
}

void GameObject::AddDrawableComponent(DrawableComponent* _drawableComponent)
{
	bool added = false;
	for(int i = 0; i < drawableComponents.size(); ++i)
	{
		if (drawableComponents[i].ZIndex == _drawableComponent->GetZIndex())
		{
			drawableComponents[i].drawableComponents.push_back(_drawableComponent);
			added = true;
			return;
		}
		if (drawableComponents[i].ZIndex > _drawableComponent->GetZIndex())
		{
			drawableComponents.insert(drawableComponents.begin() + i, DrawableLayer(_drawableComponent->GetZIndex()));
			drawableComponents[i].drawableComponents.push_back(_drawableComponent);
			added = true;
			return;
		}
	}

	if (!added)
	{
		drawableComponents.push_back(DrawableLayer(_drawableComponent->GetZIndex()));
		drawableComponents[drawableComponents.size() - 1].drawableComponents.push_back(_drawableComponent);
	}
	
}

void GameObject::RemoveDrawableComponent(DrawableComponent* _drawableComponent)
{
	for (int i = 0; i < drawableComponents.size(); i++)
	{
		if (i == _drawableComponent->GetZIndex())
		{
			drawableComponents[i].drawableComponents.RemoveElement(_drawableComponent);
			break;
		}
	}
}

TList<DrawableLayer>* GameObject::GetDrawableComponents()
{
	return &drawableComponents;
}

GameObject* GameObject::GetParent() const
{
	return parent;
}

void GameObject::SetParent(GameObject* _parent)
{
	this->parent = _parent;
}

bool GameObject::GetIsActive() const
{
	return isActive;
}

void GameObject::SetIsActive(bool is_active)
{
	isActive = is_active;
}

