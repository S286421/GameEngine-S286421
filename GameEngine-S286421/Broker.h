#pragma once
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
class Subscriber;
class IEventData;

class Broker
{
	std::unordered_map<std::string, std::queue<IEventData*>> topics;
	std::unordered_map<std::string, std::vector<Subscriber*>> subscribers;
public:
	void Subscribe(const std::string& topic, Subscriber* sub);
	void Publish(const std::string& topic, IEventData* message);
	static Broker* _instance;
	static Broker& const INSTANCE();
};