#pragma once
#include "TextInput.h"
#include "../../Sources/EngineUIElement.h"

enum AlignType
{
    AutoHorizontal,
    AutoVertical,
    Manual,
};
class InspectorProperty : public EngineUIElement
{
public:
    virtual ~InspectorProperty() override;
    void Draw(sf::RenderWindow* window) override;
    void Update(float _deltaTime) override;
    void Init(sf::RenderWindow* _window) override;
    void SetPosition(const sf::Vector2f& _position) override;

    TextUIElement* GetPropertyName() { return propertyName; }
    
    TList<TextInput*>& GetPropertyValues() { return propertyValues; }
    void AddPropertyValue(TextInput* _propertyValue);
    void AddPropertyValue();

    sf::Vector2f GetSize() const;
private:
    TextUIElement* propertyName;
    TList<TextInput*> propertyValues;

    sf::Vector2f absoluteFirstValueOffset = { 0.0f, 0.0f };
    float padding = 5.0f;

    AlignType alignType = AutoHorizontal;
};
