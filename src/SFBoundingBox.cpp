#include "SFBoundingBox.h"

SFBoundingBox::SFBoundingBox(const Point2 position, 
							 const int width, const int height) 
{
    box = { (int) position.getX(), (int) position.getY(),
	   		width, height };
}

/*
	SetPosition
		Sets the position of the bounding box
*/
void SFBoundingBox::SetPosition(Point2 & p) 
{
    box.x = (int) p.getX();
    box.y = (int) p.getY();
}

/*
	Translate
		Translates the bounding box in a given direction
*/
void SFBoundingBox::Translate(Vector2 & v) 
{
    box.x += v.getX(); 
    box.y += v.getY();
}

/*
	GetX
		Returns x position
*/
int SFBoundingBox::GetX() 
{
    return box.x;
}

/*
	GetY
		Returns y position
*/
int SFBoundingBox::GetY() 
{
    return box.y;
}

/*
	GetWidth
		Returns bounding box width
*/
int SFBoundingBox::GetWidth() 
{
    return box.w;
}

/*
	GetHeight
		Returns bounding box height
*/
int SFBoundingBox::GetHeight() 
{
    return box.h;
}

/*
	GetBox
		Returns SDL_Rect representing the bounding box
*/
SDL_Rect SFBoundingBox::GetBox() 
{
    return box;
}

/*
	CollidesWith
		Checks for an intersection with another bounding box
*/
bool SFBoundingBox::CollidesWith(const shared_ptr<SFBoundingBox> b) 
{
    return SDL_HasIntersection(&box, &b->box) == SDL_TRUE;
}
