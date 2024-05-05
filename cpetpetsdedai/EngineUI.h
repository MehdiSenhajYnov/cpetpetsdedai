#pragma once
#include "Panel.h"
#include "Headers/Engine/Object.h"
#include "Sources/EngineUIElement.h"

class EngineUI : public Object
{
public:
    EngineUI();
    EngineUI(const std::string& _name, Type* parentType);;
    AddType(EngineUI, Object::GetStaticType());

    static EngineUI* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new EngineUI();
        }
        return instance;
    }

    TList<EngineUIElement*>& GetUIElements() { return uiElements; }

private:
    static EngineUI* instance;
    TList<EngineUIElement*> uiElements;

    Panel testPanel;
};
