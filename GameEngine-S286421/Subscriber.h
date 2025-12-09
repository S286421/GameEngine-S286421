#pragma once
#include "Broker.h"
#include "Message.h"

class Subscriber
{
	Broker* broker;
public:
	Subscriber() {}
	void Subscribe(const std::string& topic)
	{
		broker->Subscribe(topic, this);
	}
	virtual void Receive(const IEventData* message, const std::string& topic) = 0;
};