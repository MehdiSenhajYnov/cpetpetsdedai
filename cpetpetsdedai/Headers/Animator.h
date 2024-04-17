#pragma once
#include <vector>
#include "Animation.h"
#include "Component.h"

class Animator : public Component
{
public:
    void Init(std::shared_ptr<GameObject> _gameObject);
    void Init(std::shared_ptr<GameObject> _gameObject, std::vector<Animation*> _animations);

    void AddAnimation(Animation* _animation);

    std::vector<Animation*>* GetAnimations();

    
    void Play(std::string _name);
    void Stop();
    void Pause();
    void Resume();
    
    void Start() override;
    void Update(float deltaTime) override;
    ~Animator() override;
private:
    std::vector<Animation*> animations;
    sf::Sprite baseSprite;
    Animation currentAnimation;

    float currentTime = 0.0f;
    int currentFrame = 0;
    
};
