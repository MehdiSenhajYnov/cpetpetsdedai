#pragma once
#include "Panel.h"
#include "Headers/Engine/Object.h"
#include "Sources/EngineUIElement.h"

class EngineUI : public Object
{
public:

    AddType(EngineUI, Object::GetStaticType())

    static EngineUI* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new EngineUI();
        }
        return instance;
    }

    TList<EngineUIElement*>& GetUIElements() { return uiElements; }

    void Init(sf::RenderWindow* _window)
    {
        window = _window;
    }

    template<isEngineUIElement T>
    T* CreateUIElement()
    {
        T* newUIElement = new T();
        newUIElement->Init(window);
        uiElements.push_back(newUIElement);
        return newUIElement;
    }

    void RemoveElement(EngineUIElement* _element);

    ~EngineUI() override;
    
private:
    static EngineUI* instance;
    TList<EngineUIElement*> uiElements;

    sf::RenderWindow* window;

    EngineUI();
    EngineUI(const std::string& _name, Type* parentType);
};
