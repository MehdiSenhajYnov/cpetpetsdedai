#pragma once
#include "Component.h"

class EditorComponent : public Component
{
public:
    EditorComponent();
    EditorComponent(const std::string& _typeName, Type* parentType);
    AddType(EditorComponent, Component::GetStaticType())
};
