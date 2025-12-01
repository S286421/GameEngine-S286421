#pragma once

class GameObject;

class I_ComponentBase
{
public:
	GameObject* ParentObject;

	virtual ~I_ComponentBase() = 0;
	virtual void Update() = 0;
	I_ComponentBase(GameObject* Parent)
	{
		ParentObject = Parent;
	}
};

