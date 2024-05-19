#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include "Component.h"
#include "../Animation.h"

class SpriteRenderer;

enum class AnimationState
{
    Playing,
    Paused,
    Stopped
};

class Animator : public Component
{
public:
    ADD_TYPE(Animator, Component, REG_TYPE)
    Animator();
    Animator(const std::string& _name, Type* parentType);
    void Init(SpriteRenderer* _spriteRenderer);
    void SetAnimations(std::vector<Animation*> _animations);

    void AddAnimation(Animation* _animation);

    std::vector<Animation*>& GetAnimations();

    AnimationState state = AnimationState::Stopped;
    
    void Play(std::string _name);
    void Stop();
    void Pause();
    void Resume();

    Animation* CreateAnimation(std::string _name, float _duration, bool _loop, std::initializer_list<std::string> _frameNames = {});
    
    void Start() override;
    void Update(float deltaTime) override;
    ~Animator() override;
private:
    std::vector<Animation*> animations;
    SpriteRenderer* spriteRenderer;
    sf::Sprite baseSprite;
    Animation* currentAnimation;

    float currentTime = 0.0f;
    int currentFrame = 0;

    float nextFrameTime = 0.0f;
    std::string frameNameToChange = "";
    
};

