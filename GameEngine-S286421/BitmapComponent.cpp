#include "BitmapComponent.h"
void BitmapComponent::Update()
{
	if (_bitmap)
		_bitmap->Draw();
}
