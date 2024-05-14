#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "ISelectable.h"
#include "../../TextUIElement.h"
#include "../../Sources/EngineUIElement.h"

enum InputType
{
    Normal,
    Alphanumeric,
    Alpha,
    Numbers,
    Integers,
    One,
    OneAlpha,
    OneNumber
};

class TextInput : public EngineUIElement, public ISelectable
{
public:
    
    AddType(TextInput, EngineUIElement)
    HeaderDefaultConstructor(TextInput)

    void Draw(sf::RenderWindow* window) override;
    void Update(float _deltaTime) override;
    
    void      Init(sf::RenderWindow* _window) override;
    sf::Color colorWithAlpha(sf::Color _tempColor, int _alpha = 255);
    void      SetPosition(const sf::Vector2f& _position) override;

    void OnUserText(char _char);

    TextUIElement* GetText() { return &text; }
    TextUIElement* GetPlaceholder() { return &placeholder; }
    sf::RectangleShape* GetBackground() { return &background; }
    sf::RectangleShape* GetCarret() { return &carret; }

    void SetTextLeftPadding(float _padding) { textLeftPadding = _padding; }
    void SetCarretLeftPadding(float _padding) { carretLeftPadding = _padding; }
    void SetCarretBlinkTime(float _time) { carretBlinkTime = _time; }

    float GetTextLeftPadding() const { return textLeftPadding; }
    float GetCarretLeftPadding() const { return carretLeftPadding; }
    float GetCarretBlinkTime() const { return carretBlinkTime; }

    sf::Vector2f GetSize() const { return background.getSize(); }
    
    Event<std::string> TextSubmit;
    
protected:
    void ChangeColor(sf::Color _newColor, SelectableState _newState) override;
    sf::Vector2f GetSelectablePosition() override;
    sf::Vector2f GetSelectableSize() override;

    virtual void UpdateCarretPosition();


private:
    void CarretOnSelect(ISelectable* _selectable);
    void ChangeCursorToTextInput(ISelectable* _selectable);
    void ChangeCursorToDefault(ISelectable* _selectable);
    void OnTextChange(const std::string& _text);

    bool ProcessCharInput(char _char);
    
    float textLeftPadding = 5.0f;
    float carretLeftPadding = 5.0f;
    float carretBlinkTime = 0.5f;

    TextUIElement text;
    TextUIElement placeholder;
    sf::RectangleShape background;
    sf::RectangleShape carret ;

    bool isCarretVisible = true;
    float carretBlinkTimer = 0.0f;

    bool isBackgroundVisible = true;
    
    InputType inputType = InputType::Normal;
    
};
