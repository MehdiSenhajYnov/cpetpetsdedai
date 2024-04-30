#include "../../Headers/Components/DrawableComponent.h"

#include "../../RendererManager.h"
#include "../../Headers/Engine/GameObject.h"

DrawableComponent::DrawableComponent() : DrawableComponent("DrawableComponent", Component::GetStaticType())
{
}

DrawableComponent::DrawableComponent(const std::string& _typeName, Type* parentType) : Component(_typeName, parentType)
{
    Scale = sf::Vector2f(1, 1);
}

DrawableComponent::~DrawableComponent()
{
    std::cout << "DrawableComponent destroyed" << std::endl;
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
