#include "../../Headers/Components/EditorComponent.h"

EditorComponent::EditorComponent() : Component("EditorComponent", Component::GetStaticType())
{
}

EditorComponent::EditorComponent(const std::string& _typeName, Type* parentType) : Component(_typeName, parentType)
{
}
