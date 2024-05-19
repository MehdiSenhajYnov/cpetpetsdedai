#include "EngineUI.h"

#include "Headers/EngineUI/ButtonUIElement.h"
#include "Headers/EngineUI/FileExplorer.h"
#include "Headers/EngineUI/Inspector.h"
#include "Headers/EngineUI/ScrollbarUIElement.h"
#include "Headers/EngineUI/ToggleButtonUIElement.h"
#include "Headers/Scenes/Scene.h"
#include "Headers/Scenes/SceneManager.h"

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

void EngineUI::Init(sf::RenderWindow* _window)
{
    window = _window;

    auto pTwo = CreateUIElement<Inspector>();
    pTwo->SetAnchorSide(Right);

    auto playButton = CreateUIElement<ToggleButtonUIElement>();
    playButton->GetText()->SetString("Play");
    playButton->SetSize({ 100, 50 });
    playButton->SetPosition( sf::Vector2f(window->getSize().x/2, 100) );

    auto testOnSelect = [playButton](ISelectable* _button)
    {
        playButton->GetText()->SetString("Stop");
        SceneManager::GetInstance()->GetCurrentScene()->sceneMode = SceneMode::PlayMode;
    };
    auto testOnDeselect = [playButton](ISelectable* _button)
    {
        playButton->GetText()->SetString("Play");
        SceneManager::GetInstance()->GetCurrentScene()->sceneMode = SceneMode::EditMode;
    };

    playButton->OnSelect.Subscribe(testOnSelect);
    playButton->OnDeselect.Subscribe(testOnDeselect);
    
    // auto pThree = CreateUIElement<ScrollbarUiElement>();
    // pThree->SetPosition({ 100, 100 });

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
{
    
}

EngineUI::EngineUI(const std::string& _name, Type* parentType): Object(_name, parentType)
{
}
