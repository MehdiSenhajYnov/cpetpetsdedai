#pragma once
#include "../Utilities/Event.h"

class GameObject;

class SelectionSystem
{
public:
    static GameObject* GetSelectedObject() { return selectedObject;}
    static void SetSelectedObject(GameObject* _object)
    {
        if (selectedObject == _object) return;
        selectedObject = _object;
        OnSelectionChanged.InvokeEvent(selectedObject);
    }
    static void DeselectObject() { SetSelectedObject(nullptr); }
    
    static bool IsSomethingSelected() { return selectedObject != nullptr; }
    static bool IsSelectedObject(const GameObject* _object) { return selectedObject == _object; }

    inline static Event<GameObject*> OnSelectionChanged;
private:
    inline static GameObject* selectedObject = nullptr;
};
