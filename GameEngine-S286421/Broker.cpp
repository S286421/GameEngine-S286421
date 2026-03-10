#include "Broker.h"
#include "Subscriber.h"

/// <summary>
/// Links the topic and sub variables, and adds them to the subscribers unordered_map
/// </summary>
/// <param name="topic"></param>
/// <param name="sub"></param>
void Broker::Subscribe(const std::string& topic, Subscriber* sub)
{
	subscribers[topic].push_back(sub);
}

/// <summary>
/// Pushes message to all items in subscribers that are linked to the given topic; calls Subscriber::Receive() to push the message
/// </summary>
/// <param name="topic"></param>
/// <param name="message"></param>
void Broker::Publish(const std::string& topic, IEventData* message)
{
	topics[topic].push(message);
	for (const auto& sub : subscribers[topic])
		sub->Receive(message, topic);
}

/// <summary>
/// Creates a broker instance and returns it; used to call the broker in other files
/// </summary>
/// <returns></returns>
Broker& const Broker::INSTANCE()
{
	if (!Broker::_instance)
		Broker::_instance = new Broker();

	return *Broker::_instance;
}
Broker* Broker::_instance = nullptr;
