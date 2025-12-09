#include "Broker.h"
#include "Subscriber.h"

void Broker::Subscribe(const std::string& topic, Subscriber* sub)
{
	subscribers[topic].push_back(sub);
}

void Broker::Publish(const std::string& topic, IEventData* message)
{
	topics[topic].push(message);
	for (const auto& sub : subscribers[topic])
		sub->Receive(message, topic);
}

Broker& const Broker::INSTANCE()
{
	if (!Broker::_instance)
		Broker::_instance = new Broker();

	return *Broker::_instance;
}
Broker* Broker::_instance = nullptr;
