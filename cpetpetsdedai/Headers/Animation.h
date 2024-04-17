#pragma once
#include <string>
#include <filesystem>
#include <iostream>
#include <sys/stat.h>
class Animation
{
public:
    Animation(std::string _name, std::string _animationPath, float _duration, bool _loop);
    std::string name;
    std::string animationPath;
    float duration;
    bool loop;
};
