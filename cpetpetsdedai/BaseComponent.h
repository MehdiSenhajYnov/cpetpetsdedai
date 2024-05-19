#pragma once
#include "Headers/Engine/Object.h"
class GameObject;
enum ComponentWorkType
{
    PlayOnly,
    EditorOnly,
    PlayAndEditor,
};
class BaseComponent : public Object
{
public:
    BaseComponent();
    BaseComponent(const std::string& _typeName, Type* parentType);
    ADD_TYPE(BaseComponent, Object, REG_TYPE)

    virtual void Init();
    virtual void InitBaseComponent(GameObject* _gameObject);

    virtual void PreDestroy(){};
    virtual ~BaseComponent() override = default;
    
    GameObject* GetAttachedObject();
    ComponentWorkType componentWorkType;

protected:
    GameObject* gameObject;
};
