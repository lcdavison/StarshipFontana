#include "SFAsset.h"

SFAsset::SFAsset(std::string name, 
				 SFASSETTYPE type, 
				 std::shared_ptr<SFWindow> window) 
				 : type(type), 
				 sf_window(window), 
				 name(name) { }

SFAsset::SFAsset(const SFAsset& a) 
{
	sprite = a.sprite;
	sf_window = a.sf_window;
	bbox = a.bbox;
	type = a.type;
}

SFAsset::~SFAsset() 
{
	bbox.reset();

	if (sprite) 
	{
		SDL_DestroyTexture(sprite);
		sprite = nullptr;
	}
}

//
//	SetupSprite
//		Loads sprite from file, and sets it up for rendering
//
void SFAsset::SetupSprite(const std::string path) 
{
	sprite = IMG_LoadTexture(sf_window->getRenderer(), path.c_str());

	if(!sprite) 
	{ 
		std::cout << name << " : Failed to load sprite" << std::endl;
		return;
	}

	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);

	int w, h;
	SDL_QueryTexture(sprite, 
					 NULL, NULL, 
					 &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w, h);
}

//
//	SetAlpha
//		Sets the alpha value of the sprite
void SFAsset::SetAlpha(const int value) 
{ 
	SDL_SetTextureAlphaMod(sprite, value); 
} 

//
//	SetPosition
//		Sets the position of the asset
//
void SFAsset::SetPosition(Point2 & point) 
{
	Vector2 v(point.getX(), point.getY());
	bbox->SetPosition(point);
}

//	
//	GetPosition
//		Gets the position of the asset
//
Point2 SFAsset::GetPosition() 
{
	return Point2(bbox->GetX(), bbox->GetY());
}

//
//	GetCenter
//		Gets the center of the asset
//
Point2 SFAsset::GetCenter() 
{
	return Point2(bbox->GetX() + bbox->GetWidth() / 2, 
				  bbox->GetY() + bbox->GetHeight() / 2);
}

//
//	IsOutsideWindow
//		Determines whether the asset is within the boundaries of the window
//
bool SFAsset::IsOutsideWindow() 
{
	return bbox->GetY() + bbox->GetHeight() < 0 
		   || bbox->GetY() > sf_window->GetHeight() 
		   || bbox->GetX() + bbox->GetWidth() < 0 
		   || bbox->GetX() > sf_window->GetWidth();
}

//
//	GetName
//		Returns asset name
std::string SFAsset::GetName() const 
{ 
	return name; 
}

//
//	GetType
//		Returns asset type
SFASSETTYPE SFAsset::GetType() const 
{ 
	return type; 
}

//
//	OnUpdate
//		Performs asset specific update code
//
void SFAsset::OnUpdate() { }                         

//
//	OnRender
//		Renders the assets sprite
//
void SFAsset::OnRender() 
{
	// 1. Get the SDL_Rect from SFBoundingBox
	SDL_Rect rect = bbox->GetBox();

	// 2. Blit the sprite onto the level
	SDL_RenderCopy(sf_window->getRenderer(), 
				   sprite, 
				   NULL, 
				   &rect);
}

//
//	GoWest
//		Moves asset left
//
void SFAsset::GoWest() 
{
	Vector2 v = Vector2(-5.0f, 0) * movement_speed;

	if(GetPosition().getX() >= 0)	bbox->Translate(v);
}

//
//	GoEast
//		Moves asset right
//
void SFAsset::GoEast() 
{
	Vector2 v = Vector2(5.0f, 0) * movement_speed;

	if(GetPosition().getX() <= sf_window->GetWidth() - bbox->GetWidth())	
	   bbox->Translate(v);
}

//
//	GoNorth
//		Moves asset up
//
void SFAsset::GoNorth() 
{
	Vector2 v = Vector2(0.0f, -5.0f) * movement_speed;
	bbox->Translate(v);
}

//
//	GoSouth
//		Moves asset down
//
void SFAsset::GoSouth() 
{
	Vector2 v = Vector2(0.0f, 5.0f) * movement_speed;
	bbox->Translate(v);
}

//
//	SetMovementSpeed
//		Sets the assets movement speed
//
void SFAsset::SetMovementSpeed(float speed) 
{ 
	movement_speed = speed; 
}

//
//	DistanceTo
//		Calculates the distance to another asset
//
float SFAsset::DistanceTo(std::shared_ptr<SFAsset> other) 
{
	return GetPosition().DistanceTo(other->GetPosition());
}

//
//	MoveTowards
//		Moves assets towards another
//
void SFAsset::MoveTowards(const std::shared_ptr<SFAsset> other) 
{
	Vector2 direction = (GetPosition() - other->GetCenter()).normalize();
	direction = direction * movement_speed;

	if(GetPosition() != other->GetCenter()) bbox->Translate(direction);
}

//
//	Lerp
//		Eases asset towards another
//
void SFAsset::Lerp(const std::shared_ptr<SFAsset> other, float time) 
{
	Vector2 direction = (GetPosition() - other->GetCenter());
	direction = direction 
				* movement_speed 
				* time;

	if(GetPosition() != other->GetCenter()) bbox->Translate(direction);
}

//
//	CollidesWith
//		Detects collsion with another asset
//
bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) 
{
	return bbox->CollidesWith(other->bbox);
}

//
//	GetBoundingBox
//		Returns the assets bounding box
//
shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() 
{
	return bbox;
}

//
//	SetNotAlive
//		Sets the assets state to dead
//
void SFAsset::SetNotAlive() 
{
	alive = false;
}

//
//	IsAlive
//		Returns the assets life state
//
bool SFAsset::IsAlive() 
{
	return alive;
}

//
//	HandleCollision
//		Handles collision if one occurs
void SFAsset::HandleCollision() 
{
	if (SFASSET_PROJECTILE == type 
		|| SFASSET_ENEMY == type) 
	{
		SetNotAlive();
	}
}
