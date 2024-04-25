#pragma once
#include "../../Headers/Components/Animator.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/TextureManager.h"


void Animator::Init(std::shared_ptr<GameObject> _gameObject, SpriteRenderer* _spriteRenderer)
{
    Component::Init(_gameObject);
    spriteRenderer = _spriteRenderer;
    baseSprite = *spriteRenderer->GetSprite();
    
}

void Animator::Init(std::shared_ptr<GameObject> _gameObject, std::vector<Animation> _animations)
{
    Component::Init(_gameObject);
    animations = _animations;
}

void Animator::AddAnimation(Animation _animation)
{
    animations.push_back(_animation);
}

std::vector<Animation>* Animator::GetAnimations()
{
    return &animations;
}

void Animator::Stop()
{
    state = AnimationState::Stopped;
    spriteRenderer->SetTexture(baseSprite.getTexture());
}

void Animator::Pause()
{
    state = AnimationState::Paused;
}

void Animator::Resume()
{
    state = AnimationState::Playing;
}

void Animator::Play(std::string _name)
{
    for (auto& anim : animations)
    {
        if (anim.name == _name)
        {
            currentAnimation = anim;

            currentTime = 0.0f;
            nextFrameTime = 0.0f;
            frameNameToChange = "";
            
            state = AnimationState::Playing;
            break;
        }
    }
}

void Animator::Start()
{
    
}



void Animator::Update(float deltaTime)
{
    if (state != AnimationState::Playing)
    {
        return;
    }
    
    currentTime += deltaTime;

    if (currentTime >= nextFrameTime)
    {
        bool isAnimationEnd = true;
        for (auto& [frameTime, frameName] : currentAnimation.timeFrames)
        {
            if (currentTime < frameTime)
            {
                nextFrameTime = frameTime;
                isAnimationEnd = false;
                break;
            }
            frameNameToChange = frameName;
        }
        spriteRenderer->SetTexture(TextureManager::Instance()->GetTexture(frameNameToChange));
        if (isAnimationEnd)
        {
            currentTime = 0.0f;
            nextFrameTime = 0.0f;
            frameNameToChange = "";
        }
    }
    
}

Animator::~Animator()
{
}