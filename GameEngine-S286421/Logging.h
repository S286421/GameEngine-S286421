#pragma once
#include <string>

class Logging
{
private:
	static Logging* _instance;
public:
	static Logging* instance();
	void WriteToFile(const std::string& buffer);
};

