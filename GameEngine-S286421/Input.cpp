#include "Input.h"
#include "Broker.h"

/// <summary>
/// Initialises the input system; nullifies the last frame's key state
/// </summary>
Input::Input()
{
	for (size_t i = 0; i < SDL_SCANCODE_COUNT; i++)
	{
		lastFrameKeyState[i] = NULL;
	}
}

/// <summary>
/// Checks for the latest input from the keyboard
/// </summary>
void Input::UpdateKeyBoard()
{
	currentKeyState = SDL_GetKeyboardState(NULL);
}

/// <summary>
/// Checks to see if a key on the keyboard has been pressed
/// </summary>
/// <param name="scanCode"></param>
/// <returns></returns>
bool Input::IsKeyDown(SDL_Scancode scanCode)
{
	bool result = false;
	if (lastFrameKeyState[scanCode] < currentKeyState[scanCode])
		result = true;

	return result;
}

/// <summary>
/// Checks to see if a key on the keyboard is being held
/// </summary>
/// <param name="scanCode"></param>
/// <returns></returns>
bool Input::IsKeyHeld(SDL_Scancode scanCode)
{
	bool result = false;
	if (lastFrameKeyState[scanCode] == currentKeyState[scanCode] && currentKeyState[scanCode] != NULL)
		result = true;

	return result;
}

/// <summary>
/// Checks to see if a key on the keyboard has been released
/// </summary>
/// <param name="scanCode"></param>
/// <returns></returns>
bool Input::IsKeyUp(SDL_Scancode scanCode)
{
	bool result = false;
	if (lastFrameKeyState[scanCode] > currentKeyState[scanCode])
		result = true;

	return result;
}

/// <summary>
/// Sets the lastFrameKeyState variable to the currentKeyState variable ready for the next frame
/// </summary>
void Input::LateUpdate()
{
	for (size_t i = 0; i < SDL_SCANCODE_COUNT; i++)
	{
		lastFrameKeyState[i] = currentKeyState[i];
	}
}

/// <summary>
/// Creates an instance of the input manager for use in main.cpp
/// </summary>
/// <returns></returns>
Input& const Input::INSTANCE()
{
	if (!Input::_instance)
		Input::_instance = new Input();

	return *Input::_instance;
}
Input* Input::_instance = nullptr;


/// <summary>
/// Used to check the movements and inputs of the mouse
/// </summary>
/// <param name="event"></param>
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
