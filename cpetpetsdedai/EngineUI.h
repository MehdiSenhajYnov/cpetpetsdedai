#pragma once
#include "Panel.h"
#include "Headers/Engine/Object.h"
#include "Sources/EngineUIElement.h"
#include "Factory.h"

namespace sf
{
    class Cursor;
}

class EngineUI : public Object
{
public:

    AddType(EngineUI, Object)

    static EngineUI* GetInstance();
    static void ResetInstance();

    TList<EngineUIElement*>& GetUIElements();

    void Init(sf::RenderWindow* _window, sf::Cursor* _cursor);

    template<typename T>
    T* CreateUIElement() requires IsDerivedFrom<T, EngineUIElement>;

    void RemoveElement(EngineUIElement* _element);

    ~EngineUI() override;
    
private:
    static EngineUI* instance;
    TList<EngineUIElement*> uiElements;

    sf::RenderWindow* window = nullptr;
    sf::Cursor* cursor = nullptr;

    EngineUI();
    EngineUI(const std::string& _name, Type* parentType);
};

template <typename T>
T* EngineUI::CreateUIElement() requires IsDerivedFrom<T, EngineUIElement>
{
    T* newUIElement = Factory::GetInstance()->CreateObject<T>();
    newUIElement->Init(window, cursor);
    uiElements.push_back(newUIElement);
    return newUIElement;
}
