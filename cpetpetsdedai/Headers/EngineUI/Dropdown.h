#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "ISelectable.h"
#include "../../Sources/EngineUIElement.h"

class VerticalAlignment;
class ButtonUIElement;
class IClickable;

class Dropdown : public EngineUIElement
{
public:
    ADD_TYPE(Dropdown, EngineUIElement, REG_TYPE)
    Dropdown() : Dropdown("Dropdown", EngineUIElement::GetStaticType()) { }
    Dropdown(const std::string& _typeName, Type* parentType) : EngineUIElement(_typeName, parentType) { }


    template<typename T>
    ButtonUIElement* AddElement(const std::string& _elementName, void(T::*_function)(IClickable*), T* _object)
    {
        return AddElement(_elementName, [_function, _object](IClickable* _arg) {
            (_object->*_function)(_arg);
        });
        
    }
    
    ButtonUIElement* AddElement(const std::string& _elementName,std::function<void(IClickable*)> _function);
    
    virtual ~Dropdown() override;
    
    void Draw(sf::RenderWindow* _window) override;
    void Update(float _deltaTime) override;
    void Init(sf::RenderWindow* _window) override;

    void SetSize(const sf::Vector2f& _size) override ;

    ButtonUIElement* GetMainButton() const { return mainButton; }

    VerticalAlignment* GetVerticalAlignment() const { return verticalAlignment; }
    void SetPosition(const sf::Vector2f& _position) override;

    void SwitchOpenClose();
    void Open();
    void Close();

    void UpdateIconPosition();

    void SetMainText(const std::string& _text);
    sf::Vector2f GetSize() const override;

protected:
    TList<ButtonUIElement*> elements;
    VerticalAlignment* verticalAlignment = nullptr;
    ButtonUIElement* mainButton = nullptr;

    sf::Sprite openIcon = sf::Sprite();
    
    bool isExpanded = false;
};
