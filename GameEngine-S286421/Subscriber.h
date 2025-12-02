#pragma once
#include "Broker.h"
#include "Message.h"

class Subscriber
{
	Broker* broker;
public:
	Subscriber(Broker& broker) : broker(&broker) {}
	void Subscribe(const std::string& topic)
	{
		broker->Subscribe(topic, this);
	}
	virtual void Receive(const Message* message, const std::string& topic) = 0;
};