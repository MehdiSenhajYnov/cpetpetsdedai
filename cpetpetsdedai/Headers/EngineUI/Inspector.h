#pragma once
#include "InspectorProperty.h"
#include "TextInput.h"
#include "../../Panel.h"

class Inspector : public Panel
{
public:
    AddType(Inspector, Panel)
    HeaderDefaultConstructor(Inspector)
    void Draw(sf::RenderWindow* _window) override;
    void Init(sf::RenderWindow* _window, sf::Cursor* _cursor) override;

    void UpdateContentNames(GameObject* _object);
    void Update(float _deltaTime) override;
    void UpdatePosition();
    void SetPosition(const sf::Vector2f& _position) override;
    void ResetSpaceHolded() override;

    TList<InspectorProperty> properties;
    
private:
    sf::Vector2f titleOffset = { 10, 10};
    
    float leftPadding = 5.0f;
    float currentMaxHeigth = 0.0f;

};
