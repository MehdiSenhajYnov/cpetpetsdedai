#pragma once
#include "Panel.h"
#include "Headers/Engine/Object.h"
#include "Sources/EngineUIElement.h"
#include "Factory.h"

class IClickable;

namespace sf
{
    class Cursor;
}

class EngineUI : public Object
{
public:

    ADD_TYPE(EngineUI, Object, REG_TYPE)

    static EngineUI* GetInstance();
    static void ResetInstance();

    TList<EngineUIElement*>& GetUIElements();

    void Init(sf::RenderWindow* _window);

    template<typename T>
    T* CreateUIElement() requires IsDerivedFrom<T, EngineUIElement>;

    void RemoveElement(EngineUIElement* _element);

    ~EngineUI() override;
    
private:
    static EngineUI* instance;
    TList<EngineUIElement*> uiElements;

    sf::RenderWindow* window = nullptr;

    EngineUI();
    EngineUI(const std::string& _name, Type* parentType);
};

template <typename T>
T* EngineUI::CreateUIElement() requires IsDerivedFrom<T, EngineUIElement>
{
    T* newUIElement = Factory::GetInstance()->CreateObject<T>();
    newUIElement->Init(window);
    uiElements.push_back(newUIElement);
    return newUIElement;
}
