#pragma once
#include "ButtonAppearance.h"
#include "ITogglable.h"

class ToggleButtonUIElement: public ButtonAppearance, public ITogglable
{
public:
    ADD_TYPE(ToggleButtonUIElement, ButtonAppearance, REG_TYPE)
    ToggleButtonUIElement() : ToggleButtonUIElement("ToggleButtonUIElement", ButtonAppearance::GetStaticType()) { }
    ToggleButtonUIElement(const std::string& _typeName, Type* parentType) : ButtonAppearance(_typeName, parentType) { }

    virtual ~ToggleButtonUIElement() override;

    void Update(float _deltaTime) override;

    void SetPosition(const sf::Vector2f& _position) override;
    void Init(sf::RenderWindow* _window) override;
protected:
    void ChangeColor(sf::Color _newColor, SelectableState _newState) override;
    sf::Vector2f GetSelectablePosition() override;
    sf::Vector2f GetSelectableSize() override;
};
