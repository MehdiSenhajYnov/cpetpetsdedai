﻿#pragma once
#include <SFML/Graphics/Text.hpp>

#include "Headers/Utilities/Event.h"
#include "Sources/EngineUIElement.h"

class TextUIElement : public EngineUIElement
{
public:
    HeaderDefaultConstructor(TextUIElement)

    void Draw(sf::RenderWindow* window) override;
    void Update(float _deltaTime) override;

    sf::Text* GetText() { return &text; }
    void SetText(const std::string& _text)
    {
        if (text.getString() == _text)
        {
            return;
        }
        text.setString(_text);
        OnTextChange.InvokeEvent(_text);
    }
    void Init(sf::RenderWindow* _window, sf::Cursor* _cursor) override;

    void SetCharacterSize(unsigned int size) { text.setCharacterSize(size); }
    void SetStyle(sf::Text::Style style) { text.setStyle(style); }
    void SetFillColor(const sf::Color& color) { text.setFillColor(color); }
    void SetString(const std::string& _text) { text.setString(_text); }
    void SetPosition(const sf::Vector2f& position) { text.setPosition(position); }

    void SetOrigin(const sf::Vector2f& origin) { text.setOrigin(origin); }

    void SetVerticalOriginToCenter()
    {
        std::string curText = text.getString();
        // $ est la caractere qui a la plus grande hauteur et q est le caractere qui a la plus petite hauteur, en mettant $q on s'assure que le texte sera centré verticalement
        text.setString("$q");
        text.setOrigin(0, GetSize().y / 2);
        text.setString(curText);
    }
    
    sf::Vector2f GetSize() const { return { text.getGlobalBounds().width, text.getGlobalBounds().height }; }

    Event<const std::string&> OnTextChange;
    
private:
    sf::Text text;
    static sf::Font font;
    static bool fontLoaded;
};
