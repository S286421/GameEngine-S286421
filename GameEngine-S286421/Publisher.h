#pragma once
#include <string>
#include "Broker.h"
class Message;

class Publisher
{
	Broker* broker;
public:
	Publisher(Broker& broker) : broker(&broker) {}
	void Publish(const std::string& topic, Message* message) const
	{
		broker->Publish(topic, message);
	}
};