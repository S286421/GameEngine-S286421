#pragma once
#include "IEventData.h"
#include "SDL3/SDL.h"
class MouseEventData : public IEventData
{
public:

	MouseEventData(Publisher& sender, SDL_MouseButtonEvent MouseButton,
		SDL_MouseMotionEvent MousePosition,
		SDL_MouseWheelEvent MouseWheel) : IEventData(sender),
		mouseButton(MouseButton),
		mousePosition(MousePosition),
		mouseWheel(MouseWheel) {};

	SDL_MouseButtonEvent mouseButton;
	SDL_MouseMotionEvent mousePosition;
	SDL_MouseWheelEvent mouseWheel;
};

