#pragma once
#include <string>
#include <filesystem>
#include <iostream>
#include <initializer_list>
#include <map>

class Animation
{
public:
    Animation();
    
    void Init(std::string _name, float _duration, bool _loop, std::initializer_list<std::string> _frameNames);
    void AddFrames(std::initializer_list<std::string> _frameNames);
    std::vector<float> GenerateAutoFrameTime(float duration, int counters);
    void ChangeFrameTime(float currentTimeFrame, float newTime);

    std::string name;
    std::vector<std::string> frameNames;
    std::map<float, std::string> timeFrames;
    
    float duration;
    bool loop;
    float regularNextFrameStep;
};
