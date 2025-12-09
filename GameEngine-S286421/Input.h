#pragma once
#include "SDL3/SDL.h"
#include "MouseEventData.h"
#include "Publisher.h"

class Input : public Publisher
{
public:
	void UpdateKeyBoard();
	void UpdateMouse(const SDL_Event& event);
	
	bool lastFrameKeyState[SDL_SCANCODE_COUNT];
	const bool* currentKeyState;
	bool IsKeyDown(SDL_Scancode scanCode);
	bool IsKeyHeld(SDL_Scancode scanCode);
	bool IsKeyUp(SDL_Scancode scanCode);
	void LateUpdate();
	static Input* _instance;
	static Input& const INSTANCE();

	Input();

	SDL_MouseButtonEvent mouseButton;
	SDL_MouseMotionEvent mousePosition;
	SDL_MouseWheelEvent mouseWheel;
};

