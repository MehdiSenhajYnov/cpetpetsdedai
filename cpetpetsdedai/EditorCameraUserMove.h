#pragma once
#include "Headers/Components/Component.h"

class EditorCameraUserMove : public Component
{
public:
    ADD_TYPE(EditorCameraUserMove, Component, REG_TYPE)
    EditorCameraUserMove();

    void Start() override;
    void Update(float deltaTime) override;

private:
    sf::Vector2f lastMousePosition = { 0, 0 };
    sf::Vector2f deltaMousePosition = { 0, 0 };
};
