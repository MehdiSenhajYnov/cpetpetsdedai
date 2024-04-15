#include "../Headers/GameObject.h"

GameObject::GameObject(std::string _name) : Name(_name)
{
}

sf::Sprite* GameObject::GetSprite()
{
	return &sprite;
}

void GameObject::SetSprite(std::string texturepath)
{
	if (spriteTexture.loadFromFile(texturepath))
	{
		spriteTexture.setSmooth(true);
		sprite.setTexture(spriteTexture);
	}
	else
	{
		std::cout << "error with load texture " << std::endl;
	}
}


void GameObject::SetSprite(std::string texturepath, sf::IntRect textureRect)
{
	if (spriteTexture.loadFromFile(texturepath, textureRect))
	{
		spriteTexture.setSmooth(true);
		sprite.setTexture(spriteTexture);
	}
	else
	{
		std::cout << "error with load texture " << std::endl;
	}
}


void GameObject::SetPosition(sf::Vector2<float> _newposition)
{

	position = _newposition;
}

void GameObject::SetPosition(float _x, float _y)
{
	position = sf::Vector2<float>(_x, _y);
}

void GameObject::SetRotation(float _newRotation)
{
	GetSprite()->setRotation(_newRotation);
}

sf::Vector2<float> GameObject::GetPosition()
{
	return position;
}

float GameObject::GetRotation()
{
	return GetSprite()->getRotation();
}

sf::Vector2<float>* GameObject::GetPositionPointer()
{
	return &position;
}

void GameObject::Move(float _x, float _y)
{
	if (position.x + _x >= std::numeric_limits<float>::max() || position.y + _y >= std::numeric_limits<float>::max())
	{
		std::cout << "out of limit MAX position" << std::endl;
		return;
	}
	if (position.x + _x <= std::numeric_limits<float>::min() || position.y + _y <= std::numeric_limits<float>::min())
	{
		auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };
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
		auto vectorToStr = [](sf::Vector2f toconvert) { return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); };
		std::cout << "out of limit MIN position" << std::endl;
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
