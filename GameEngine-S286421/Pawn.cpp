#include "Pawn.h"
#include "imgui.h"
#include "EditorGui.h"


/// <summary>
/// Returns the pawn's x position
/// </summary>
/// <returns></returns>
int Pawn::GetX()
{
	return Position.x;
}

/// <summary>
/// Sets the pawn's x position to the specified x value
/// </summary>
/// <param name="x"></param>
void Pawn::SetX(int x)
{
	Position.x = x;
}

/// <summary>
/// Returns the pawn's y position
/// </summary>
/// <returns></returns>
int Pawn::GetY()
{
	return Position.y;
}

/// <summary>
/// Sets the pawn's y position to the specified y value
/// </summary>
/// <param name="y"></param>
void Pawn::SetY(int y)
{
	Position.y = y;
}

/// <summary>
/// Sets the pawn's position to the specified x and y values
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Pawn::UpdatePosition(int x, int y)
{
	DeltaMove.x += x;
	DeltaMove.y += y;
}

int Pawn::CurrentID = 0;

/// <summary>
/// Initialises the pawn; creates a bitmap from the given values
/// </summary>
/// <param name="renderer"></param>
/// <param name="path"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="isTransparent"></param>
/// <param name="pawnName"></param>
Pawn::Pawn(std::shared_ptr<SDL_Renderer> renderer, const std::string path, int x, int y, bool isTransparent, std::string pawnName)
{
	Sprite = std::unique_ptr<Bitmap>(new Bitmap(renderer, path, x, y, isTransparent));
	this->Position.x = x;
	this->Position.y = y;

	ID = CurrentID++;
	PawnName = pawnName;
}

/// <summary>
/// Calls the Bitmap::Draw(int x, int y) function for the pawn
/// </summary>
void Pawn::Draw()
{
	Sprite->Draw(Position.x, Position.y);
	//this->DrawCollider(this->GetCollisionBounds());
}

void Pawn::Update()
{
}

/// <summary>
/// Return the collision bounds of the pawn as a SDL_Rect
/// </summary>
/// <returns></returns>
SDL_Rect Pawn::GetCollisionBounds() const
{
	return Sprite->GetImageBounds();
}

/// <summary>
/// Draws the collider of the pawn; used in debugging collisions
/// </summary>
/// <param name="Collider"></param>
void Pawn::DrawCollider(SDL_Rect Collider) const
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
	SDL_GetRenderDrawColor(Sprite->GetRenderer().get(), &R, &G, &B, &A);

	SDL_SetRenderDrawColor(Sprite->GetRenderer().get(), 255, 255, 255, 255);

	const SDL_FRect dstRect = { static_cast<float>(Collider.x), static_cast<float>(Collider.y), static_cast<float>(Collider.w), static_cast<float>(Collider.h) };
	SDL_RenderRect(Sprite->GetRenderer().get(), &dstRect);
	SDL_SetRenderDrawColor(Sprite->GetRenderer().get(), R, G, B, A);
}

/// <summary>
/// Sets the Delta Move of the pawn to the specified x and y values
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void Pawn::SetDeltaMove(int x, int y)
{
	DeltaMove.x = x;
	DeltaMove.y = y;
}

/// <summary>
/// Receives input data from the mouse; used to open debug windows for pawn entities
/// </summary>
/// <param name="EventData"></param>
/// <param name="topic"></param>
void Pawn::Receive(const IEventData* EventData, const std::string& topic)
{
	const MouseEventData* mouseEventData = static_cast<const MouseEventData*>(EventData);
	if (topic == "MousePositionUpdate")
	{ }
	if (topic == "MouseWheelUpdate")
	{ }
	if (topic == "MouseButtonUpdate")
	{
		SDL_Point mousePosition{ mouseEventData->mousePosition.x, mouseEventData->mousePosition.y };
		SDL_Rect ImageBounds = Sprite.get()->GetImageBounds();

		if (mouseEventData->mouseButton.button == SDL_BUTTON_LEFT && mouseEventData->mouseButton.clicks == 1 && SDL_PointInRect(&mousePosition, &ImageBounds) && mouseEventData->mouseButton.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			std::cout << "clicked on image" << std::endl;
			EditorGui::INSTANCE().AttachChildWindow(this);
		}
	}

}

/// <summary>
/// Detects if the pawn entity is interacting with any other entities
/// </summary>
/// <param name="ListOfOtherpawns"></param>
/// <param name="Delta"></param>
/// <returns></returns>
bool Pawn::IsOverlapping(const std::vector<Pawn*>& ListOfOtherpawns, const SDL_Point& Delta)
{
	bool isColliding = false;
	currentCollisions = {};

	SDL_Rect a = Sprite->GetImageBounds();
	a.x = Position.x;
	a.y = Position.y;
	a.x += Delta.x;
	
	for (int i = 0; i < ListOfOtherpawns.size(); i++)
	{
		SDL_Rect b = ListOfOtherpawns[i]->Sprite->GetImageBounds();
		b.x = ListOfOtherpawns[i]->Position.x;
		b.y = ListOfOtherpawns[i]->Position.y;

		if (SDL_HasRectIntersection(&a, &b))
		{

			if (Delta.x > 0)
				a.x = b.x - a.w; // right
			else if (Delta.x < 0)
				a.x = b.x + b.w; //left
			isColliding = true;
			currentCollisions.push_back(ListOfOtherpawns[i]);
		}
		
	}

	a.y += Delta.y;
	for (int i = 0; i < ListOfOtherpawns.size(); i++)
	{
		SDL_Rect b = ListOfOtherpawns[i]->Sprite->GetImageBounds();
		b.x = ListOfOtherpawns[i]->Position.x;
		b.y = ListOfOtherpawns[i]->Position.y;

		if (SDL_HasRectIntersection(&a, &b))
		{
			if (Delta.y > 0) a.y = b.y - a.h;
			else if (Delta.y < 0) a.y = b.y + b.h;
			isColliding = true;
			currentCollisions.push_back(ListOfOtherpawns[i]);

		}
	}
			
	Position.x = a.x;
	Position.y = a.y;

	return isColliding;
}


/// <summary>
/// Draws an ImGui window for the pawn; used for debugging values
/// </summary>
void Pawn::DrawWindow()
{
	ImGui::Begin((std::string("Pawn Window") + std::to_string(ID)).c_str());

	if (ImGui::Button("Close"))
	{
		EditorGui::INSTANCE().RemoveChildWindow(dynamic_cast<IGuiWindow*>(this));
	}

	int pos[2] = { Position.x, Position.y };
	ImGui::InputInt2("Position", pos);
	Position.x = pos[0];
	Position.y = pos[1];

	ImGui::InputInt("Speed", &speed);
	ImGui::InputInt("Gravity", &gravity);
	ImGui::InputInt("Max Fall Speed", &maxFallSpeed);
	ImGui::InputFloat("Y Velocity", &yVelocity);

	ImGui::End();
}

/// <summary>
/// Calls the Bitmap::DrawAnimation() function for the pawn
/// </summary>
/// <param name="moveSprites"></param>
/// <param name="Frame"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void Pawn::DrawAnimation(const std::vector< SDL_Texture*> &moveSprites, int Frame, int x, int y)
{
	Sprite->DrawAnimation(moveSprites, Frame, x, y);
}

