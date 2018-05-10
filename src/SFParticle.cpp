#include "SFParticle.h"

SFParticle::SFParticle(int x, int y,
		       int alpha,
		       std::shared_ptr<SFWindow> window)
  		       : sfwindow(window) 
{
	sprite = IMG_LoadTexture(sfwindow->getRenderer(), "assets/sprites/smoke.png");

	if(sprite == NULL) 
	   std::cout << "Failed to find sprite" << std::endl;
	
	SDL_SetTextureBlendMode(sprite, SDL_BLENDMODE_BLEND);

	SDL_SetTextureAlphaMod(sprite, alpha);

	bbox = std::make_shared<SFBoundingBox>(Point2(x, y), 10, 10);

	frame = std::rand() % 5;
}

SFParticle::~SFParticle() 
{
	if(sprite) 
	{
		SDL_DestroyTexture(sprite);
		sprite = nullptr;
	}
}

/*
	OnUpdate
		Updates the particle each frame
*/
void SFParticle::OnUpdate() 
{
	float angle_degrees = atan2(bbox->GetY(), bbox->GetX())
	  		      * 180 / M_PI
	  		      * std::rand();

	int x = bbox->GetX()
	  	+ cos(angle_degrees)
	  	* 0.02f;
	
	int y = bbox->GetY()
	  	+ sin(angle_degrees)
	  	* -0.02f;

	Point2 pos = Point2(x, y);
	bbox->SetPosition(pos);
}

/*
	OnRender
		Renders the particle
*/
void SFParticle::OnRender() 
{
	SDL_Rect rect = bbox->GetBox();
	SDL_RenderCopy(sfwindow->getRenderer(), sprite, NULL, &rect);
	frame++;
}

/*
	IsDead
		Determines whether the particle is dead
*/
bool SFParticle::IsDead() 
{ 
	return frame > 30; 
}
