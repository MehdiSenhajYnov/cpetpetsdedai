#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/TextureManager.h"
#include "../../Headers/Components/Component.h"

GameObject::GameObject(): GameObject("GameObject", Object::GetStaticType())
{
}

GameObject::GameObject(const std::string& _name, Type* parentType) : Object(_name, parentType)
{
	SERIALIZE_FIELD(name)
	SERIALIZE_FIELD(position)
	SERIALIZE_FIELD(scale)
	SERIALIZE_FIELD(positionType)
	SERIALIZE_FIELD(isActive)
	SERIALIZE_FIELD(parent)
	SERIALIZE_FIELD(_tags)

	auto _componentsSetInvoke = [this](decltype(components) _newValue)
	{
		this->components = _newValue;
		for (auto& _component : components)
		{
			_component->Start();
		}
	};
	std::function<decltype(components)()> _componentsGetInvoke = [this]() { return this->components; };
	GetType()->CreateField<decltype(components)>("components", _componentsSetInvoke, _componentsGetInvoke);
}


GameObject::~GameObject()
{
	for (auto& _componentToDelete : components)
	{
		Factory::GetInstance()->DestroyObject(_componentToDelete);
	}
	components.clear();
	_tags.clear();
}

void GameObject::Init(const std::string& _name)
{
	name = _name;
}

void GameObject::ComponentsManagement()
{
	if (componentsToAdd.size() > 0)
	{
		components.AppendVector(componentsToAdd);
		componentsToAdd.clear();
	}
	if (componentsToRemove.size() > 0)
	{
		for (auto& _componentToRemove : componentsToRemove)
		{
			components.RemoveElement(_componentToRemove);
			Factory::GetInstance()->DestroyObject(_componentToRemove);
		}
		componentsToRemove.clear();
	}
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
		std::cout << "out of limit MAX position" << std::endl;
		return;
	}
	if (position.x + _x <= std::numeric_limits<float>::min() || position.y + _y <= std::numeric_limits<float>::min())
	{
		std::cout << "out of limit MIN position" << std::endl;
		return;
	}

	SetPosition(GetPosition().x + _x, GetPosition().y + _y);
}

void GameObject::Move(sf::Vector2f _moveBy)
{
	if ((position + _moveBy).x >= std::numeric_limits<float>::max() || (position + _moveBy).y >= std::numeric_limits<float>::max())
	{
		std::cout << "out of limit MAX position" << std::endl;
		return;
	}
	if ((position + _moveBy).x <= -std::numeric_limits<float>::max() || (position + _moveBy).y <= -std::numeric_limits<float>::max())
	{
		std::cout << "out of limit MIN position" << std::endl;
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

TList<Component*>& GameObject::GetComponents()
{
	return components;
}

Component* GameObject::AddComponentByName(const std::string& _typeName)
{
	Object* _obj = Factory::GetInstance()->CreateObjectByName(_typeName);
	if (_obj == nullptr)
	{
		std::cout << "Component with name " << _typeName << " not found" << std::endl;
		return nullptr;
	}
	Component* component = dynamic_cast<Component*>(_obj);
	if (component)
	{
		component->InitBaseComponent(this);
		components.push_back(component);
		component->Start();
		return component;
	}
	std::cout << _typeName << " is not a component" << std::endl;
	Factory::GetInstance()->DestroyObject(_obj);
	return nullptr;
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

