#pragma once
#include <SDL3/SDL.h>
#include <vector>
struct Transform
{
public:
	std::vector<Transform*> Children;
	SDL_Point Location = {0,0};
	SDL_Point WorldLocation;

	/// <summary>
	/// Adds the given Transform* to the Children vector
	/// </summary>
	/// <param name="child"></param>
	void AddChild(Transform* child)
	{
		Children.push_back(child);
	}

	/// <summary>
	/// Removes the given Transform* from the Children vector
	/// </summary>
	/// <param name="child"></param>
	void removeChild(Transform* child)
	{
		auto it = std::remove(Children.begin(), Children.end(), child);
		if (it != Children.end())
			Children.erase(it, Children.end());
	}

	/// <summary>
	/// Updates the position of the parent object, then calls the same transform for every child in the Children vector
	/// </summary>
	/// <param name="parentTransform"></param>
	void UpdateTransform(const Transform& parentTransform)
	{
		WorldLocation.x = Location.x + parentTransform.Location.x;
		WorldLocation.y = Location.y + parentTransform.Location.y;

		for (Transform* child : Children)
		{
			child->UpdateTransform(*this);
			
		}
	}

	/// <summary>
	/// Returns the x position as an int
	/// </summary>
	/// <returns></returns>
	int GetX()
	{
		return Location.x;
	}
};