#pragma once
#include "ISelectable.h"

class ITogglable : public ISelectable
{
protected:
    void OnMouseKeyDown() override;

public:
    
};
