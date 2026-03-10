#include "Logging.h"

Logging* Logging::_instance = NULL;

/// <summary>
/// Creates a logger instance and returns it; used to call the logger in other files
/// </summary>
/// <returns></returns>
Logging* Logging::instance()
{
	if (!_instance) _instance = new Logging();
	return _instance;
}

/// <summary>
/// Allows for the given buffer string to be written into error.log
/// </summary>
/// <param name="buffer"></param>
void Logging::WriteToFile(const std::string& buffer)
{
	FILE* logFile = NULL;

	fopen_s(&logFile, "error.log", "a+");

	if (!logFile) return;

	fprintf_s(logFile, buffer.c_str());

	fclose(logFile);
}
