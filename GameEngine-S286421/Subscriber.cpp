#include "Subscriber.h"

Subscriber::Subscriber()
{
}

/// <summary>
/// Subscribes the object it is assigned to to the given topic; uses Broker::Subscribe() to link the topic and subscriber
/// </summary>
/// <param name="topic"></param>
void Subscriber::Subscribe(const std::string& topic)
{
	Broker::INSTANCE().Subscribe(topic, this);
}
