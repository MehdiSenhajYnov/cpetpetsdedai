#include "AlignmentBase.h"

void AlignmentBase::AddToContextMenu(EngineUIElement* _elementInstance)
{
    if (_elementInstance == nullptr)
    {
        return;
    }
    if (!_elementInstance->GetIsInitialized())
    {
        _elementInstance->Init(window);
    }
    elements.push_back(_elementInstance);
    UpdatePositionOfElement(_elementInstance, elements.size() - 1);
}

bool AlignmentBase::IsInside(sf::Vector2f _mousePosition) const
{
    if (_mousePosition.x > GetPosition().x && _mousePosition.x < currentTopRight.x && _mousePosition.y > GetPosition().y && _mousePosition.y < currentBottomLeft.y)
    {
        return true;
    }
    return false;
}

void AlignmentBase::Enable()
{
    isActive = true;
}

void AlignmentBase::Disable()
{
    isActive = false;
}

sf::Vector2f AlignmentBase::GetSize() const
{
    return currentBottomRight - GetPosition();
}

void AlignmentBase::Draw(sf::RenderWindow* _window)
{
    if (!isActive) return;
    for (auto& element : elements)
    {
        element->Draw(window);
    }
}

void AlignmentBase::Update(float _deltaTime)
{
    if (!isActive) return;
    for (auto& element : elements)
    {
        if (element == nullptr) continue;
        element->Update(_deltaTime);
    }

    for (int i = 0; i < elements.size(); ++i)
    {
        UpdatePositionOfElement(elements[i], i);
    }
}

void AlignmentBase::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);
    for (int i = 0; i < elements.size(); ++i)
    {
        UpdatePositionOfElement(elements[i], i);
    }
}
