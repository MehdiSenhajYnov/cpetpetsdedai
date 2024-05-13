#include "../../Headers/Components/DrawableComponent.h"

#include "../../RendererManager.h"
#include "../../Headers/Engine/GameObject.h"

DefaultConstructor(DrawableComponent, Component)

DrawableComponent::~DrawableComponent()
{
}

sf::Vector2f DrawableComponent::GetCurrentSize()
{
    return {GetOriginalSize().x * Scale.x, GetOriginalSize().y * Scale.y};
}

void DrawableComponent::InitBaseComponent(GameObject* _gameObject)
{
    Component::InitBaseComponent(_gameObject);
    Init();
}

void DrawableComponent::Init()
{
    if (alreadyInit)
    {
        return;
    }
    gameObject->AddDrawableComponent(this);
    alreadyInit = true;
}

void DrawableComponent::PreDestroy()
{
    gameObject->RemoveDrawableComponent(this);
    Component::PreDestroy();

}

void DrawableComponent::Update(float deltaTime)
{
    RendererManager::GetInstance()->AddDrawableLayer(this);
}

sf::Vector2f DrawableComponent::GetScale() const
{
    return Scale;
}

void DrawableComponent::SetScale(sf::Vector2f _scale)
{
    Scale = _scale;
}

sf::Vector2f DrawableComponent::GetOffsetPosition() const
{
    return OffsetPosition;
}

void DrawableComponent::SetOffsetPosition(sf::Vector2f _offsetPosition)
{
    OffsetPosition = _offsetPosition;
}
