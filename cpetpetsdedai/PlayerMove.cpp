#include "PlayerMove.h"

#include "Headers/Engine/GameObject.h"
#include "Headers/Utilities/MyMath.h"

PlayerMove::PlayerMove() : PlayerMove("PlayerMove", Component::GetStaticType())
{
}

PlayerMove::PlayerMove(const std::string& _name, Type* parentType) : Component(_name, parentType)
{
    SERIALIZE_FIELD(speed)
}

void PlayerMove::Start()
{
}

void PlayerMove::Update(float deltaTime)
{
    MoveDirection = { 0, 0 };
    if (Input::GetKey(leftKey))
    {
        MoveDirection.x += -1;
    }
    if (Input::GetKey(rightKey))
    {
        MoveDirection.x += 1;
    }
    gameObject->Move(MoveDirection * speed * deltaTime);

    // auto tempresult = Input::GetKeysDown();
    // for (auto& key : tempresult)
    // {
    //     std::cout << "key down: " << key << std::endl;
    // }
}
