#include "ITogglable.h"

void ITogglable::OnMouseKeyDown()
{
    if (isMouseHover )
    {
        if (selectableState != SelectableState::Selected)
        {
            isMousePressingTheSelectable = true;
            ClickOnTheSelectable = true;
            tempState = SelectableState::Pressed;
            OnMouseClickDown.InvokeEvent(this);
        }
        else
        {
            Deselect();
        }    
    }
}
