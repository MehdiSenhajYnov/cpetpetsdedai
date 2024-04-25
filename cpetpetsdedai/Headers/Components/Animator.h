#pragma once
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include "Component.h"
#include "SpriteRenderer.h"
#include "../Animation.h"
enum class AnimationState
{
    Playing,
    Paused,
    Stopped
};

class Animator : public Component
{
public:
    void Init(std::shared_ptr<GameObject> _gameObject, SpriteRenderer* _spriteRenderer);
    void Init(std::shared_ptr<GameObject> _gameObject, std::vector<Animation> _animations);

    void AddAnimation(Animation _animation);

    std::vector<Animation>* GetAnimations();

    AnimationState state = AnimationState::Stopped;
    
    void Play(std::string _name);
    void Stop();
    void Pause();
    void Resume();
    
    void Start() override;
    void Update(float deltaTime) override;
    ~Animator() override;
private:
    std::vector<Animation> animations;
    SpriteRenderer* spriteRenderer;
    sf::Sprite baseSprite;
    Animation currentAnimation;

    float currentTime = 0.0f;
    int currentFrame = 0;

    

    float nextFrameTime = 0.0f;
    std::string frameNameToChange = "";
    
};

