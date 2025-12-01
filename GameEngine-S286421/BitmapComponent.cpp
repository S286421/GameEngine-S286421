#include "BitmapComponent.h"
#include "GameObject.h"
void BitmapComponent::Update()
{
	if (_bitmap)
		_bitmap->Draw(ParentObject->transform.WorldLocation.x, ParentObject->transform.WorldLocation.y);
}
