#include "Subscriber.h"

Subscriber::Subscriber()
{
}

void Subscriber::Subscribe(const std::string& topic)
{
	Broker::INSTANCE().Subscribe(topic, this);
}
