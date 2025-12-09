#pragma once
#include <string>
#include "Broker.h"
class IEventData;

class Publisher
{
	Broker* broker;
public:
	Publisher() {}
	void Publish(const std::string& topic, IEventData* EventData) const
	{
		Broker::INSTANCE().Publish(topic, EventData);
	}
};