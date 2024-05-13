#include "EngineUIElement.h"

void EngineUIElement::ChangeCursor(sf::Cursor::Type cursorType)
{
    // CRASHING When called multiple times
    if (cursor == nullptr)
    {
        return;
    }
    if (window == nullptr)
    {
        return;
    }
    if (cursorType == currentCursor)
    {
        return;
    }
    cursor->loadFromSystem(cursorType);
    window->setMouseCursor(*cursor);
    currentCursor = cursorType;
}
