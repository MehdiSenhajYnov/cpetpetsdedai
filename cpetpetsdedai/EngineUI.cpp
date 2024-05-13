#include "EngineUI.h"

#include "Headers/EngineUI/FileExplorer.h"
#include "Headers/EngineUI/Inspector.h"


EngineUI* EngineUI::instance = nullptr;

EngineUI* EngineUI::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new EngineUI();
    }
    return instance;
}

void EngineUI::ResetInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

TList<EngineUIElement*>& EngineUI::GetUIElements()
{
    return uiElements;
}

void EngineUI::Init(sf::RenderWindow* _window, sf::Cursor* _cursor)
{
    window = _window;
    cursor = _cursor;
    
    auto pOne = CreateUIElement<FileExplorer>();
    pOne->SetAnchorSide(Bottom);

    auto pTwo = CreateUIElement<Inspector>();
    pTwo->SetAnchorSide(Right);
    
}

void EngineUI::RemoveElement(EngineUIElement* _element)
{
    uiElements.RemoveElement(_element);
    Factory::GetInstance()->DestroyObject(_element);
}

EngineUI::~EngineUI()
{
    for(auto& uiElement : uiElements)
    {
        Factory::GetInstance()->DestroyObject(uiElement);
    }
    uiElements.clear();
}

EngineUI::EngineUI(): EngineUI("EngineUI", Object::GetStaticType())
{ }

EngineUI::EngineUI(const std::string& _name, Type* parentType): Object(_name, parentType)
{
}
