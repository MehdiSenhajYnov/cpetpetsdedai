#pragma once
#include "Headers/Components/Component.h"
#include "Headers/Input/Input.h"

class PlayerMove : public Component
{
public:
    ADD_TYPE(PlayerMove, Component, REG_TYPE)
    PlayerMove();
    PlayerMove(const std::string& _name, Type* parentType);
    void Start() override;
    void Update(float deltaTime) override;

private:

    float speed = 100.0f;
    sf::Vector2f MoveDirection = { 0, 0 };

    KeyCode jumpKey = KeyCode::Space;
    KeyCode leftKey = KeyCode::Q;
    KeyCode rightKey = KeyCode::D;
};
