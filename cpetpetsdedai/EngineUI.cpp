#include "EngineUI.h"

EngineUI* EngineUI::instance = nullptr;

EngineUI::EngineUI(): EngineUI("EngineUI", Object::GetStaticType())
{ }

EngineUI::EngineUI(const std::string& _name, Type* parentType): Object(_name, parentType)
{
    uiElements.push_back(&testPanel);
}
