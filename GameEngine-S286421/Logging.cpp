#include "Logging.h"

Logging* Logging::_instance = NULL;

Logging* Logging::instance()
{
	if (!_instance) _instance = new Logging();
	return _instance;
}

void Logging::WriteToFile(const std::string& buffer)
{
	FILE* logFile = NULL;

	fopen_s(&logFile, "error.log", "a+");

	if (!logFile) return;

	fprintf_s(logFile, buffer.c_str());

	fclose(logFile);
}
