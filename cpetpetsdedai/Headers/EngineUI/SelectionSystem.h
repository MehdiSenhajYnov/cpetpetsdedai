#pragma once
#include "../Utilities/Event.h"

class GameObject;

class SelectionSystem
{
public:
    static GameObject* GetSelectedObject(const std::string& _systemName)
    {
        if (selectedObjectsBySystemName.contains(_systemName))
        {
            return selectedObjectsBySystemName[_systemName];
        }
        return nullptr;
    }
    static void SetSelectedObject(GameObject* _object, const std::string& _systemName)
    {
        //if (selectedObjectsBySystemName.contains(_systemName) )
        if (_object != nullptr)
        {
            selectedObjectsBySystemName[_systemName] = _object;
        } else
        {
            selectedObjectsBySystemName.erase(_systemName);
        }
        OnSelectionChanged.InvokeEvent(_object, _systemName);
    }
    
    static void DeselectObject(const std::string& _systemName)
    {
        SetSelectedObject(nullptr, _systemName);
    }
    
    static bool IsSomethingSelected(const std::string& _systemName)
    {
        return selectedObjectsBySystemName.contains(_systemName) && selectedObjectsBySystemName[_systemName] != nullptr;
    }
    static bool IsSelectedObject(const GameObject* _object, const std::string& _systemName)
    {
        return selectedObjectsBySystemName.contains(_systemName) && selectedObjectsBySystemName[_systemName] == _object;
    }

    inline static Event<GameObject*, std::string> OnSelectionChanged;
private:
    //inline static GameObject* selectedObject = nullptr;

    inline static std::map<std::string, GameObject*> selectedObjectsBySystemName;
};
