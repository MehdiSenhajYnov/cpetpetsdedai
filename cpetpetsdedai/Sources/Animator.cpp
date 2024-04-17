#include "../Headers/Animator.h"

void Animator::Init(std::shared_ptr<GameObject> _gameObject)
{
    LoadComponentBase(_gameObject);
    baseSprite = *gameObject->GetSprite();
    
}

void Animator::Init(std::shared_ptr<GameObject> _gameObject, std::vector<Animation*> _animations)
{
    LoadComponentBase(_gameObject);
    animations = _animations;
}

void Animator::AddAnimation(Animation* _animation)
{
    animations.push_back(_animation);
}

std::vector<Animation*>* Animator::GetAnimations()
{
    return &animations;
}

void Animator::Stop()
{
}

void Animator::Pause()
{
}

void Animator::Resume()
{
}

void Animator::Play(std::string _name)
{
}

void Animator::Start()
{
}

Animator::~Animator()
{
}

void Animator::Update(float deltaTime)
{
}
