#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/TextureManager.h"
#include "../../Headers/Components/Component.h"

GameObject::GameObject(): Object("GameObject", Object::GetStaticType())
{
}

void GameObject::InitGameObject(std::string _name)
{
}

// sf::Sprite* GameObject::GetSprite()
// {
// 	return &sprite;
// }
//
// void GameObject::SetSprite(const std::string& texturepath)
// {
// 	spriteTexture = TextureManager::Instance()->GetTexture(texturepath);
// 	if (spriteTexture == nullptr)
// 	{
// 		std::cout << "Texture not found" << '\n';
// 		return;
// 	}
// 	sprite.setTexture(*spriteTexture);
// }
//
//
// void GameObject::SetSprite(const std::string& _spriteName, sf::IntRect textureRect)
// {
// 	spriteTexture = TextureManager::Instance()->GetTexture(_spriteName);
// 	//TODO: Set the texture rectangle
//
// 	if (spriteTexture == nullptr)
// 	{
// 		std::cout << "Texture not found" << '\n';
// 		return;
// 	}
// 	sprite.setTexture(*spriteTexture);
//
// }
//
// void GameObject::SetTexture(sf::Texture* _texture)
// {
// 	spriteTexture = _texture;
// 	if (spriteTexture == nullptr)
// 	{
// 		std::cout << "Texture not found" << '\n';
// 		return;
// 	}
// 	sprite.setTexture(*spriteTexture);
// }

void GameObject::SetPosition(sf::Vector2<float> _newposition)
{
	position = _newposition;
}

void GameObject::SetPosition(float _x, float _y)
{
	position = sf::Vector2<float>(_x, _y);
}

void GameObject::SetScale(sf::Vector2<float> _newScale)
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

sf::Vector2<float> GameObject::GetPosition()
{
	return position;
}


sf::Vector2<float>* GameObject::GetPositionPointer()
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

void GameObject::AddTags(std::string tagToAdd)
{
	_tags.push_back(tagToAdd);
}

void GameObject::RemoveTags(std::string tagToRemove)
{
	for (int i = 0; i < _tags.size(); i++)
	{
		if (_tags[i] == tagToRemove)
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

void GameObject::AddComponent(Component* _component)
{
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i] == _component)
		{
			components.erase(components.begin() + i);
			return;
		}
	}
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
