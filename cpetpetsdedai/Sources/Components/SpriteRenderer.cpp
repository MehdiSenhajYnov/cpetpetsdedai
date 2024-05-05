#include "../../Headers/Components/SpriteRenderer.h"

#include "../../Headers/GameSystem/TextureManager.h"

SpriteRenderer::SpriteRenderer() : DrawableComponent("SpriteRenderer", DrawableComponent::GetStaticType())
{
    
}

void SpriteRenderer::Start()
{
}


SpriteRenderer::~SpriteRenderer()
{
}

sf::Sprite* SpriteRenderer::GetSprite()
{
    return &sprite;
}

void SpriteRenderer::SetSprite(const std::string& texturepath)
{
    spriteTexture = TextureManager::Instance()->GetTexture(texturepath);
    if (spriteTexture == nullptr)
    {
        std::cout << "Texture not found" << '\n';
        return;
    }
    sprite.setTexture(*spriteTexture);
    
    ResetOrigin();
}

void SpriteRenderer::SetSprite(const std::string& _spriteName, sf::IntRect textureRect)
{
    spriteTexture = TextureManager::Instance()->GetTexture(_spriteName);
    //TODO: Set the texture rectangle

    if (spriteTexture == nullptr)
    {
        std::cout << "Texture not found" << '\n';
        return;
    }
    sprite.setTexture(*spriteTexture);
    ResetOrigin();
}

void SpriteRenderer::SetTexture(sf::Texture* _texture)
{
    spriteTexture = _texture;
    if (spriteTexture == nullptr)
    {
        std::cout << "Texture not found" << '\n';
        return;
    }
    sprite.setTexture(*spriteTexture);
    ResetOrigin();
}

void SpriteRenderer::SetTexture(const sf::Texture* _texture)
{
    SetTexture(const_cast<sf::Texture*>(_texture));
    ResetOrigin();
}

void SpriteRenderer::SetColor(sf::Color _color)
{
    color = _color;
    sprite.setColor(color);
}

sf::Color SpriteRenderer::GetColor()
{
    return color;
}

const sf::Drawable* SpriteRenderer::GetDrawable()
{
    return &sprite;
}

void SpriteRenderer::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

sf::FloatRect SpriteRenderer::GetBounds()
{
    return sprite.getLocalBounds();
}

sf::Vector2f SpriteRenderer::GetOriginalSize()
{
    if (sprite.getTexture() == nullptr)
    {
        return sf::Vector2f(0, 0);
    }
	return sf::Vector2f(
        GetSprite()->getTexture()->getSize().x,
        GetSprite()->getTexture()->getSize().y
    );
}

void SpriteRenderer::SetOrigin(sf::Vector2f origin)
{
    sprite.setOrigin(origin);
}

void SpriteRenderer::ResetOrigin()
{
    SetOrigin({GetCurrentSize().x/2, GetCurrentSize().y/2});
}

void SpriteRenderer::SetDrawScale(sf::Vector2f _drawScale)
{
    sprite.setScale(_drawScale);
}

sf::Vector2f SpriteRenderer::GetCenter() const
{
    return sf::Vector2f(sprite.getLocalBounds().left + sprite.getLocalBounds().width / 2.0f,
        sprite.getLocalBounds().top + sprite.getLocalBounds().height / 2.0f);
}


