#pragma once
#include "InspectorProperty.h"
#include "ScrollbarUIElement.h"
#include "TextInput.h"
#include "../../Panel.h"

class Dropdown;
class VerticalAlignment;

class Inspector : public Panel
{
public:
    ADD_TYPE(Inspector, Panel, REG_TYPE)
    HeaderDefaultConstructor(Inspector)

    virtual ~Inspector() override;
    
    void Draw(sf::RenderWindow* _window) override;
    void Init(sf::RenderWindow* _window) override;

    void UpdateSelectedObject(GameObject* _object, std::string _selectionSystemName);
    void InitPropertiesOnUpdate(GameObject* _object);
    void InitComponentsOnUpdate(GameObject* _object, BaseField* _baseElement);
    void InitDropdownOnUpdate();
    void InitScrollbarOnUpdate();

    void AddProperty(BaseField* _field);

    void Update(float _deltaTime) override;
    void UpdatePosition();
    void OnScrollbarMove(sf::Vector2f _newPos, float _pourcentage);
    void SetPosition(const sf::Vector2f& _position) override;
    void ResetSpaceHolded() override;

    TList<InspectorProperty*> properties;
    std::map<InspectorProperty*, BaseField*> propertiesFields;
    VerticalAlignment* verticalList = nullptr;
    Dropdown* dropdown = nullptr;
    bool haveToRefreshInspector = false;

    void ValueSubmitted(std::string _textInput, std::string baseText, BaseField* _field, InspectorProperty* curproperty);
    ScrollbarUiElement scrollbar = ScrollbarUiElement();

    void OnWindowResize(sf::Vector2u _newSize);
    
private:
    sf::Vector2f titleOffset = { 10, 10};
    
    float leftPadding = 5.0f;
    float currentMaxHeigth = 0.0f;
    float currentMaxWidth = 0.0f;

    float scrollBarPourcentage = 0.0f;

    sf::Vector2u currentWindowSize;

    const std::string SELECTION_SYSTEM_NAME = "INSPECTOR";
};
