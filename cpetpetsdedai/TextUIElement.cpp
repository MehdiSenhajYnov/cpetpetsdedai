#include "TextUIElement.h"

#include "RendererManager.h"

DefaultConstructor(TextUIElement, EngineUIElement)

sf::Font TextUIElement::font;
bool TextUIElement::fontLoaded;

void TextUIElement::Draw(sf::RenderWindow* _window)
{
    window->draw(text);
}

void TextUIElement::Update(float _deltaTime)
{
}

void TextUIElement::SetText(const std::string& _text)
{
    if (text.getString() == _text)
    {
        return;
    }
        
    text.setString(_text);
    OnTextChange.InvokeEvent(_text);
}

void TextUIElement::Init(sf::RenderWindow* _window)
{
    EngineUIElement::Init(_window);
    text = sf::Text();
    if (!fontLoaded)
    {
        if (!font.loadFromFile("./Fonts/Arial.ttf"))
        {
            std::cout << "ERROR" << std::endl;
        }
        else
        {
            fontLoaded = true;
        }

    }
    text.setFont(font);
    text.setCharacterSize(25);
    text.setStyle(sf::Text::Regular);
    text.setFillColor(sf::Color::Black);
}
