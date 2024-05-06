#include "Panel.h"
#include <SFML/Graphics/RenderWindow.hpp>

sf::Drawable* Panel::GetDrawable()
{
    return nullptr;
}

void Panel::Init(sf::RenderWindow* window)
{
    EngineUIElement::Init(window);
}

void Panel::Update()
{
    line[0].position = sf::Vector2f(10, 0);
    line[1].position = sf::Vector2f(20, 0);

    switch (GetAnchorSide())
    {
    case Left:
        line[0].position = sf::Vector2f(GetSize(), 0);
        line[1].position = sf::Vector2f(GetSize(), window->getSize().y);
        break;
    case Right:
        line[0].position = sf::Vector2f(((float)window->getSize().x)- GetSize(), 0);
        line[1].position = sf::Vector2f(((float)window->getSize().x)- GetSize(), window->getSize().y);
        break;
    case Top:
        line[0].position = sf::Vector2f(0, GetSize());
        line[1].position = sf::Vector2f(window->getSize().x, GetSize());
        break;
    case Bottom:
        line[0].position = sf::Vector2f(0, ((float)window->getSize().y)-GetSize());
        line[1].position = sf::Vector2f(window->getSize().x, ((float)window->getSize().y)-GetSize());
        break;
    }

    line->color = sf::Color::Red;
}

void Panel::Draw(sf::RenderWindow* window)
{
    
    
	window->draw(line, 2, sf::Lines);
}
