#pragma once
#include <string>

class Message
{
	std::string message;
public:
	Message(std::string message) : message(message) {}
	std::string getMessage() const { return message; }
};