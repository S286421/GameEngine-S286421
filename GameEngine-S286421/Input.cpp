#include "Input.h"

Input::Input()
{
	for (size_t i = 0; i < SDL_SCANCODE_COUNT; i++)
	{
		lastFrameKeyState[i] = NULL;
	}
}

void Input::Update()
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
