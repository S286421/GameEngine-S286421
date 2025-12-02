#include "Broker.h"
#include "Subscriber.h"

void Broker::Subscribe(const std::string& topic, Subscriber* sub)
{
	subscribers[topic].push_back(sub);
}

void Broker::Publish(const std::string& topic, Message* message)
{
	topics[topic].push(message);
	for (const auto& sub : subscribers[topic])
		sub->Receive(message, topic);
}
