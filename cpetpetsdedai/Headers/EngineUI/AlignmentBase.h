#pragma once
#include "../../Sources/EngineUIElement.h"

class AlignmentBase : public EngineUIElement
{
public:
    ADD_TYPE(AlignmentBase, EngineUIElement, REG_TYPE)
    AlignmentBase(const std::string& _typeName, Type* parentType) : EngineUIElement(_typeName, parentType) { }
    
    template<typename T>
    T* AddToContextMenu() requires IsBaseOf<EngineUIElement, T>
    {
        T* elementInstance = Factory::GetInstance()->CreateObject<T>();
        elementInstance->Init(window);
        elements.push_back(elementInstance);
        UpdatePositionOfElement(elementInstance, elements.size() - 1);
        return elementInstance;
    }

    virtual void AddToContextMenu(EngineUIElement* _elementInstance);

    virtual bool IsInside(sf::Vector2f _mousePosition) const;

    virtual void UpdatePositionOfElement(EngineUIElement* _elementInstance, int _index) = 0;

    
    void Enable();

    void Disable();

    virtual sf::Vector2f GetSize() const override;

    virtual void Draw(sf::RenderWindow* _window) override;
    virtual void Update(float _deltaTime) override;

    TList<EngineUIElement*> GetElements() const { return elements; }

    float GetSpaceBetweenButtons() const { return spaceBetweenButtons; }
    void SetSpaceBetweenButtons(float _spaceBetweenButtons) { spaceBetweenButtons = _spaceBetweenButtons; }
    void SetPosition(const sf::Vector2f& _position) override;

protected:
    TList<EngineUIElement*> elements;

    float spaceBetweenButtons = 10;

    sf::Vector2f currentTopRight = {0,0};
    sf::Vector2f currentBottomLeft = {0,0};
    sf::Vector2f currentBottomRight = {0,0};
    
    bool isActive = true;

};
