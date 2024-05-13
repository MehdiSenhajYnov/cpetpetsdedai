#pragma once
#include "../../Panel.h"

class FileExplorer : public Panel
{
public:
    AddType(FileExplorer, Panel)
    HeaderDefaultConstructor(FileExplorer)
    
    void Draw(sf::RenderWindow* _window) override;
    TList<TextUIElement> contentNames;
};
