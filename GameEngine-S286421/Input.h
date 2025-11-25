#pragma once
#include "SDL3/SDL.h"

class Input
{
public:
	void Update();
	
	bool lastFrameKeyState[SDL_SCANCODE_COUNT];
	const bool* currentKeyState;
	bool IsKeyDown(SDL_Scancode scanCode);
	bool IsKeyHeld(SDL_Scancode scanCode);
	bool IsKeyUp(SDL_Scancode scanCode);
	void LateUpdate();
	static Input* _instance;
	static Input& const INSTANCE();

	Input();
};

