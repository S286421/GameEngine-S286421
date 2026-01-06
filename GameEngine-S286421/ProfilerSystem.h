#pragma once
#include <cstdint>
#include <map>
#include <vector>
#include <fstream>
#include <string>

struct SampleData
{
	int64_t frameTime;
	int frameReference;
};
typedef std::map<const char*, std::vector<SampleData*>> FrameMap;

class ProfilerSystem
{
public:
	static ProfilerSystem& Instance()
	{
		static ProfilerSystem INSTANCE;
		return INSTANCE;
	}

	ProfilerSystem();
	~ProfilerSystem();

	void StartFrame();
	void StoreSample(const char* name, int64_t elapsedTime);
	void EndFrame();
	void WriteDataToCSV();

	FrameMap& GetFrameData() const;
	int GetCurrentFrame() const;
	FrameMap& GetLastFrameData() const;
	std::vector<float>& GetFrameTimes();

private:
	int currentFrame;
	FrameMap* frameData;
	std::vector<float> totalFrameTimes;
	float thisFramesTotalTime = 0;
	FrameMap* thisFramesFrameData;
	FrameMap* lastFramesFrameData;
};

struct Profile
{
	Profile(const char* name)
	{
		_name = name;
		startTime = std::clock();
	}

	~Profile()
	{
		std::clock_t endTime = std::clock();
		std::clock_t elapsedTime = endTime - startTime;

		ProfilerSystem::Instance().StoreSample(_name, (1000 * elapsedTime) / CLOCKS_PER_SEC);
	}

	const char* _name;
	std::clock_t startTime;
};
#define PROFILE(name) Profile p(name)

