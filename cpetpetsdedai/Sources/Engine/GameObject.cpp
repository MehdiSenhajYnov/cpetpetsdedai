#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/TextureManager.h"
#include "../../Headers/Components/Component.h"
#include "../../Headers/Components/DrawableComponent.h"
#include "../../Headers/Utilities/Utilities.h"

#define LOG(Var)\
	std::cout << Var;



GameObject::GameObject(): GameObject("GameObject", Object::GetStaticType())
{
	std::string test = "intializing";
	LOG(test);
}

GameObject::GameObject(const std::string& _name, Type* parentType) : Object(_name, parentType),
	positionType(World), scale(1,1), position(0,0), isActive(true), parent(nullptr)
{
	
	// auto _changeNameInvoke = [this](std::string _newValue)
	// {
	// 	this->name = _newValue;
	// };
	// GetType()->CreateField<std::string>("name", _changeNameInvoke);
	
	SerializeField(std::string, name);
	SerializeField(sf::Vector2f, position);
	SerializeField(sf::Vector2f, scale);
	SerializeField(PositionType, positionType);
	SerializeField(bool, isActive);
	SerializeField(GameObject*, parent);
	SerializeField(TList<std::string>, _tags);
	SerializeField(TList<Component*>, components);

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

void GameObject::Init(const std::string& _name)
{
	name = _name;
}

void GameObject::SetPosition(const sf::Vector2f& _newposition)
{
	position = _newposition;
}

void GameObject::SetPosition(float _x, float _y)
{
	position = sf::Vector2f(_x, _y);
}

void GameObject::SetScale(const sf::Vector2f& _newScale)
{
	scale = _newScale;
}

void GameObject::SetScale(const float& _x, const float& _y)
{
	scale = sf::Vector2f(_x, _y);
}

std::string GameObject::GetName()
{
	return name;
}

void GameObject::SetName(const std::string& _name)
{
	name = _name;
}

sf::Vector2f GameObject::GetPosition() const
{
	return position;
}

sf::Vector2f* GameObject::GetPositionPointer()
{
	return &position;
}

void GameObject::Move(const float& _x, const float& _y)
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

sf::Vector2f GameObject::GetScale() const
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

