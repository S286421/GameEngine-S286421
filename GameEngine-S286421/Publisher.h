#pragma once
#include <string>
#include "Broker.h"
class IEventData;

class Publisher
{
	Broker* broker;
public:
	Publisher() {}

	/// <summary>
	/// Calls Broker::Publish() using the given topic and EventData
	/// </summary>
	/// <param name="topic"></param>
	/// <param name="EventData"></param>
	void Publish(const std::string& topic, IEventData* EventData) const
	{
		Broker::INSTANCE().Publish(topic, EventData);
	}
};