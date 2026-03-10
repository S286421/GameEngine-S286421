#pragma once
#include "IEventData.h"
#include <string>
class Message : public IEventData
{
	std::string message;
public:
	Message(const Publisher& sender, std::string message) : IEventData(sender), message(message) {}

	/// <summary>
	/// Returns the std::string message
	/// </summary>
	/// <returns></returns>
	std::string getMessage() const { return message; }
};

