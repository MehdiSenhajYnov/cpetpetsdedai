#pragma once
#include "ButtonAppearance.h"
#include "IClickable.h"

class ButtonUIElement: public ButtonAppearance, public IClickable
{
public:
    ADD_TYPE(ButtonUIElement, ButtonAppearance, REG_TYPE)
    ButtonUIElement() : ButtonUIElement("ButtonUIElement", ButtonAppearance::GetStaticType()) { }
    ButtonUIElement(const std::string& _typeName, Type* parentType) : ButtonAppearance(_typeName, parentType) { }
    
    virtual ~ButtonUIElement() override;
    
    void Update(float _deltaTime) override;
    
    void SetPosition(const sf::Vector2f& _position) override;
    void Init(sf::RenderWindow* _window) override;

protected:
    sf::Vector2f GetClickablePosition() override;
    sf::Vector2f GetClickableSize() override;
    void ChangeColor(sf::Color _newColor, ClickableState _newState) override;
};
