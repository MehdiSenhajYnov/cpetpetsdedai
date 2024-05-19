#pragma once
#include "../../Panel.h"

class FileExplorer : public Panel
{
public:
    ADD_TYPE(FileExplorer, Panel, REG_TYPE)
    HeaderDefaultConstructor(FileExplorer)
    
    void Draw(sf::RenderWindow* _window) override;
    TList<TextUIElement> contentNames;
};
