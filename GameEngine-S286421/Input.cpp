#include "Input.h"
#include "Broker.h"

Input::Input()
{
	for (size_t i = 0; i < SDL_SCANCODE_COUNT; i++)
	{
		lastFrameKeyState[i] = NULL;
	}
}

void Input::UpdateKeyBoard()
{
	currentKeyState = SDL_GetKeyboardState(NULL);
}

bool Input::IsKeyDown(SDL_Scancode scanCode)
{
	bool result = false;
	if (lastFrameKeyState[scanCode] < currentKeyState[scanCode])
		result = true;

	return result;
}

bool Input::IsKeyHeld(SDL_Scancode scanCode)
{
	bool result = false;
	if (lastFrameKeyState[scanCode] == currentKeyState[scanCode] && currentKeyState[scanCode] != NULL)
		result = true;

	return result;
}

bool Input::IsKeyUp(SDL_Scancode scanCode)
{
	bool result = false;
	if (lastFrameKeyState[scanCode] > currentKeyState[scanCode])
		result = true;

	return result;
}

void Input::LateUpdate()
{
	for (size_t i = 0; i < SDL_SCANCODE_COUNT; i++)
	{
		lastFrameKeyState[i] = currentKeyState[i];
	}
}

Input& const Input::INSTANCE()
{
	if (!Input::_instance)
		Input::_instance = new Input();

	return *Input::_instance;
}
Input* Input::_instance = nullptr;

void Input::UpdateMouse(const SDL_Event& event)
{
	MouseEventData* mouseEventData = nullptr;

	switch (event.type) {

	case SDL_EVENT_MOUSE_MOTION:
		mousePosition = event.motion;
		mouseEventData = new MouseEventData(*this, mouseButton, mousePosition, mouseWheel);
		Broker::INSTANCE().Publish("MousePositionUpdate", mouseEventData);
		break;
	case SDL_EVENT_MOUSE_WHEEL:
		mouseWheel = event.wheel;
		mouseEventData = new MouseEventData(*this, mouseButton, mousePosition, mouseWheel);
		Broker::INSTANCE().Publish("MouseWheelUpdate", mouseEventData);
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP:
		mouseButton = event.button;
		mouseEventData = new MouseEventData(*this, mouseButton, mousePosition, mouseWheel);
		Broker::INSTANCE().Publish("MouseButtonUpdate", mouseEventData);
		break;
	default:
		break;
	}
	delete mouseEventData;
	mouseEventData = nullptr;
}
