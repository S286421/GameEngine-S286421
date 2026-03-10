#include "Debug.h"

int g_verbosity = 4;

/// <summary>
/// Returns charsWritten and outputs the s_buffer as a debug string
/// </summary>
/// <param name="format"></param>
/// <param name="argList"></param>
/// <returns></returns>
int VDebugPrintF(const char* format, va_list argList)
{
	const unsigned int MAX_CHARS = 1024;
	static char s_buffer[MAX_CHARS];

	int charsWritten = vsnprintf(s_buffer, MAX_CHARS, format, argList);

	OutputDebugStringA(s_buffer);
	Logging::instance()->WriteToFile(s_buffer);

	return charsWritten;
}

/// <summary>
/// Calls Debug::VDebugPrintF(); seperate function required to start and end a va_list
/// </summary>
/// <param name="format"></param>
/// <param name=""></param>
/// <returns></returns>
int DebugPrintF(const char* format, ...)
{
	va_list argList;
	va_start(argList, format);

	int charsWritten = VDebugPrintF(format, argList);

	va_end(argList);

	return charsWritten;

}

/// <summary>
/// Almost identical to Debug::DebugPrintF, but includes a verbosity level; this allows to avoid messages that are lower than g_verbosity
/// </summary>
/// <param name="verbosity"></param>
/// <param name="format"></param>
/// <param name=""></param>
/// <returns></returns>
int VerboseDebugPrintF(int verbosity, const char* format, ...)
{
	if (g_verbosity < verbosity) return 0;

	va_list argList;
	va_start(argList, format);

	int charsWritten = VDebugPrintF(format, argList);

	va_end(argList);

	return charsWritten;
}
