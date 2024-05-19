#include "../../Headers/Components/DrawableComponent.h"

#include "../../RendererManager.h"
#include "../../Headers/Engine/GameObject.h"

DrawableComponent::DrawableComponent() : DrawableComponent("DrawableComponent", Component::GetStaticType()) { }
DrawableComponent::DrawableComponent(const std::string& _typeName, Type* parentType) : Component(_typeName, parentType)
{
    SERIALIZE_FIELD(alreadyInit)
    SERIALIZE_FIELD(Scale)
    SERIALIZE_FIELD(OffsetPosition)
    SERIALIZE_FIELD(ZIndex)
}

DrawableComponent::~DrawableComponent()
{
}

sf::Vector2f DrawableComponent::GetCurrentSize()
{
    sf::Vector2f result = {GetOriginalSize().x * Scale.x, GetOriginalSize().y * Scale.y};

    // if (GetAttachedObject() != nullptr)
    // {
    //     result.x *= GetAttachedObject()->GetScale().x;
    //     result.y *= GetAttachedObject()->GetScale().y;
    // }
    
    return result;
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
    alreadyInit = true;
}

void DrawableComponent::PreDestroy()
{
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

sf::Vector2f DrawableComponent::GetOrigin() const
{
    return Origin;
}

void DrawableComponent::SetOrigin(const sf::Vector2f _origin)
{
    Origin = _origin;
    InternalSetOrigin(_origin);
}

sf::Vector2f DrawableComponent::GetOffsetPosition() const
{
    return OffsetPosition;
}

void DrawableComponent::SetOffsetPosition(sf::Vector2f _offsetPosition)
{
    OffsetPosition = _offsetPosition;
}
