#pragma once
#include <stdarg.h>
#include <cstdio>
#include <windows.h>
#include <debugapi.h>
#include "Logging.h"

extern int VDebugPrintF(const char* format, va_list argList);

extern int DebugPrintF(const char* format, ...);

extern int g_verbosity;

extern int VerboseDebugPrintF(int verbosity, const char* format, ...);

enum Verbosity
{
	None,
	Error,
	Warning,
	Info,
	All
};
