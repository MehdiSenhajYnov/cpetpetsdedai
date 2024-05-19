#include "../../Headers/Components/SpriteRenderer.h"

#include "../../Headers/GameSystem/TextureManager.h"


SpriteRenderer::SpriteRenderer() : SpriteRenderer("SpriteRenderer", DrawableComponent::GetStaticType()) { }
SpriteRenderer::SpriteRenderer(const std::string& _typeName, Type* parentType) : DrawableComponent(_typeName, parentType)
{
    SERIALIZE_FIELD_CSET(spriteName, &SpriteRenderer::SetSprite)
    SERIALIZE_FIELD_CSET(color, &SpriteRenderer::SetColorCSET)
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

// y a pas const std::string& pour pouvoir utiliser le serializeField facilement
void SpriteRenderer::SetSprite(std::string _spriteName)
{
    spriteName = _spriteName;
    spriteTexture = TextureManager::Instance()->GetTexture(_spriteName);
    if (spriteTexture == nullptr)
    {
        std::cout << "Texture not found" << std::endl;
        return;
    }
    sprite.setTexture(*spriteTexture);
    sprite.setTextureRect(sf::IntRect(0, 0, spriteTexture->getSize().x, spriteTexture->getSize().y));
    
    ResetOrigin();
}

void SpriteRenderer::SetSprite(const std::string& _spriteName, sf::IntRect textureRect)
{
    spriteName = _spriteName;
    spriteTexture = TextureManager::Instance()->GetTexture(_spriteName);
    if (spriteTexture == nullptr)
    {
        std::cout << "Texture not found" << std::endl;
        return;
    }
    sprite.setTexture(*spriteTexture);
    sprite.setTextureRect(textureRect);
    
    ResetOrigin();
}

void SpriteRenderer::SetTexture(sf::Texture* _texture)
{
    spriteTexture = _texture;
    if (spriteTexture == nullptr)
    {
        std::cout << "Texture not found" << std::endl;
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

void SpriteRenderer::SetColorCSET(sf::Color _color)
{
    SetColor(_color);
}

void SpriteRenderer::SetColor(const sf::Color& _color)
{
    color = _color;
    sprite.setColor(color);
}

sf::Color SpriteRenderer::GetColor() const
{
    return color;
}

const sf::Drawable* SpriteRenderer::GetDrawable()
{
    return &sprite;
}

void SpriteRenderer::setPosition(sf::Vector2f _pos)
{
    sprite.setPosition(_pos);
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
        (float)GetSprite()->getTexture()->getSize().x,
        (float)GetSprite()->getTexture()->getSize().y
    );
}

void SpriteRenderer::ResetOrigin()
{
    SetOrigin({GetCurrentSize().x/2, GetCurrentSize().y/2});
}

void SpriteRenderer::SetDrawScale(sf::Vector2f _drawScale)
{
    sprite.setScale(_drawScale);
    ResetOrigin();
}

sf::Vector2f SpriteRenderer::GetCenter() const
{
    return sf::Vector2f(sprite.getLocalBounds().left + sprite.getLocalBounds().width / 2.0f,
        sprite.getLocalBounds().top + sprite.getLocalBounds().height / 2.0f);
}

void SpriteRenderer::InternalSetOrigin(const sf::Vector2f _origin)
{
    sprite.setOrigin(_origin);
}

void SpriteRenderer::SetScale(sf::Vector2f _scale)
{
    DrawableComponent::SetScale(_scale);
}


