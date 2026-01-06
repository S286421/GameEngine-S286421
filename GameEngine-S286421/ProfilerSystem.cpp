#include "ProfilerSystem.h"

FrameMap& ProfilerSystem::GetFrameData() const
{
	return *frameData;
}

int ProfilerSystem::GetCurrentFrame() const
{
	return currentFrame;
}

FrameMap& ProfilerSystem::GetLastFrameData() const
{
	return *lastFramesFrameData;
}

std::vector<float>& ProfilerSystem::GetFrameTimes()
{
	return totalFrameTimes;
}

void ProfilerSystem::WriteDataToCSV()
{
	std::ofstream CSVFile;
	CSVFile.open("../Assets/Profile.csv");

	for (auto const& [name, samples] : *frameData)
	{
		std::string frametime = "";
		std::string frameRef = "";
		CSVFile << name << "\n";
		for (SampleData* sample : samples)
		{
			frameRef += std::to_string(sample->frameReference) + ",";
			frametime += std::to_string(sample->frameTime) + ",";
		}
		frameRef += "\n";
		frametime += "\n";
		CSVFile << frameRef;
		CSVFile << frametime;
	}
	CSVFile << ",\n";
	CSVFile.close();
}

ProfilerSystem::ProfilerSystem()
{
	frameData = new FrameMap();
	thisFramesFrameData = new FrameMap();
	lastFramesFrameData = new FrameMap();
}

ProfilerSystem::~ProfilerSystem()
{
}

void ProfilerSystem::StartFrame()
{
	currentFrame++;
	thisFramesTotalTime = 0;
}

void ProfilerSystem::StoreSample(const char* name, int64_t elapsedTime)
{
	SampleData* sample = new SampleData();
	sample->frameReference = currentFrame;
	sample->frameTime = elapsedTime;

	thisFramesTotalTime += elapsedTime;

	(*frameData)[name].push_back(sample);
	(*thisFramesFrameData)[name].push_back(sample);
}

void ProfilerSystem::EndFrame()
{
	totalFrameTimes.push_back(thisFramesTotalTime);
	lastFramesFrameData = thisFramesFrameData;
	thisFramesFrameData = new FrameMap();
}
