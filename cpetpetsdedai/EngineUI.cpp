#include "EngineUI.h"

EngineUI* EngineUI::instance = nullptr;

void EngineUI::RemoveElement(EngineUIElement* _element)
{
    uiElements.RemoveElement(_element);
    delete _element;
    _element = nullptr;
}

EngineUI::~EngineUI()
{
    for(auto& uiElement : uiElements)
    {
        delete uiElement;
        uiElement = nullptr;
    }
    uiElements.clear();
}

EngineUI::EngineUI(): EngineUI("EngineUI", Object::GetStaticType())
{ }

EngineUI::EngineUI(const std::string& _name, Type* parentType): Object(_name, parentType)
{
    CreateUIElement<Panel>();
}
