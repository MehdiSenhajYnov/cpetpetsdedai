#include "../Headers/Animation.h"


Animation::Animation()
{
}



void Animation::Init(std::string _name, float _duration, bool _loop, std::initializer_list<std::string> _frameNames)
{
	name = _name;
	duration = _duration;
	loop = _loop;
	frameNames = _frameNames;
	
	auto generatedframeTimes = GenerateAutoFrameTime(duration, frameNames.size());
	int i = 0;
	for (auto& frameName : frameNames)
	{
		timeFrames[generatedframeTimes[i]] = frameName;
		i++;
	}

	regularNextFrameStep = duration / frameNames.size();
	
}

void Animation::AddFrames(std::initializer_list<std::string> _frameNames)
{
	for (auto& frameName : _frameNames)
	{
		frameNames.push_back(frameName);
		duration += regularNextFrameStep;
		timeFrames[duration] = frameName;
	}
}

std::vector<float> Animation::GenerateAutoFrameTime(float duration, int counters) {
	std::vector<float> result;
	float step = duration / counters;
	for (int i = 0; i <= counters; ++i) {
		result.push_back(step * i);
	}
	return result;
}

void Animation::ChangeFrameTime(float currentTimeFrame, float newTime)
{
	if (timeFrames.contains(currentTimeFrame))
	{
		std::string frameName = timeFrames[currentTimeFrame];
		timeFrames.erase(currentTimeFrame);
		timeFrames[newTime] = frameName;
	}

	
}