#include "../../Headers/Components/Animator.h"

#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/GameSystem/TextureManager.h"

Animator::Animator(): Animator("Animator", Component::GetStaticType())
{ }

Animator::Animator(const std::string& _name, Type* parentType): Component(_name, parentType), spriteRenderer(nullptr)
{
    //SERIALIZE_FIELD(animations)
    //SERIALIZE_FIELD(baseSprite)
    SERIALIZE_FIELD(spriteRenderer)
}

void Animator::Init(SpriteRenderer* _spriteRenderer)
{
    spriteRenderer = _spriteRenderer;
    baseSprite = *spriteRenderer->GetSprite();
    
}

void Animator::SetAnimations(std::vector<Animation*> _animations)
{
    animations = _animations;
}

void Animator::AddAnimation(Animation* _animation)
{
    animations.push_back(_animation);
}

std::vector<Animation*>& Animator::GetAnimations()
{
    return animations;
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

Animation* Animator::CreateAnimation(std::string _name, float _duration, bool _loop,
    std::initializer_list<std::string> _frameNames)
{
    Animation* newAnimation = new Animation();
    newAnimation->Init(_name, _duration, _loop, _frameNames);
    animations.push_back(newAnimation);
    return newAnimation;
}

void Animator::Play(std::string _name)
{
    for (auto& anim : animations)
    {
        if (anim->name == _name)
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
        for (auto& [frameTime, frameName] : currentAnimation->timeFrames)
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
    for (auto& element : animations)
    {
        delete element;
        element = nullptr;
    }
    animations.clear();
}