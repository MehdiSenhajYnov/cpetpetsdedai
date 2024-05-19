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

enum SizeType
{
    Adaptive,
    Fixed,
    FixedNoBlock,
};

class TextInput : public EngineUIElement, public ISelectable
{
public:
    
    ADD_TYPE(TextInput, EngineUIElement, REG_TYPE)
    HeaderDefaultConstructor(TextInput)

    void Draw(sf::RenderWindow* _window) override;
    void Update(float _deltaTime) override;
    
    void      Init(sf::RenderWindow* _window) override;
    sf::Color colorWithAlpha(sf::Color _tempColor, int _alpha = 255);
    void      SetPosition(const sf::Vector2f& _position) override;

    void AdaptSize();
    void OnUserText(char _char);

    TextUIElement* GetText() { return &text; }
    TextUIElement* GetPlaceholder() { return &placeholder; }
    sf::RectangleShape* GetBackground() { return &background; }
    sf::RectangleShape* GetCarret() { return &carret; }

    void SetTextLeftPadding(float _padding) { textPadding.x = _padding; }
    void SetCarretLeftPadding(float _padding) { carretLeftPadding = _padding; }
    void SetCarretBlinkTime(float _time) { carretBlinkTime = _time; }
    void SetText(const std::string& _newText);

    float GetTextLeftPadding() const { return textPadding.x; }
    float GetCarretLeftPadding() const { return carretLeftPadding; }
    float GetCarretBlinkTime() const { return carretBlinkTime; }

    sf::Vector2f GetSize() const override { return background.getSize(); }
    void SetSize(const sf::Vector2f& _size) override;
    
    Event<std::string> TextSubmit;
    
protected:
    void ChangeColor(sf::Color _newColor, SelectableState _newState) override;
    sf::Vector2f GetSelectablePosition() override;
    sf::Vector2f GetSelectableSize() override;

    virtual void UpdateCarretPosition();


private:
    void ChangeCarretIndex(int _newIndex);
    void IncreaseCarretIndex();
    void DecreaseCarretIndex();
    void CarretOnSelect(ISelectable* _selectable);
    void ChangeCursorToTextInput(ISelectable* _selectable);
    void ChangeCursorToDefault(ISelectable* _selectable);

    bool ProcessCharInput(char _char);
    
    //float textLeftPadding = 5.0f;
    sf::Vector2f textPadding = { 5.0f, 5.0f };
    float carretLeftPadding = 5.0f;
    float carretBlinkTime = 0.5f;

    TextUIElement text;
    TextUIElement placeholder;
    sf::RectangleShape background;
    sf::RectangleShape carret;

    bool isCarretVisible = true;
    float carretBlinkTimer = 0.0f;

    bool isBackgroundVisible = true;
    
    InputType inputType = InputType::Normal;


    SizeType sizeType = SizeType::Adaptive;

    
    sf::Vector2f minSize = { 50.0f, 50.0f };
    sf::Vector2f maxSize = { 200.0f, 1000.0f };
    bool haveMaxSize = false;
    int carretIndex = 0;
    
};
