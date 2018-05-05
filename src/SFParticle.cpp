#include "SFParticle.h"

// TODO: Add Alpha Blending

SFParticle::SFParticle(int x, int y, std::shared_ptr<SFWindow> window) : sfwindow(window) 
{
	sprite = IMG_LoadTexture(sfwindow->getRenderer(), "assets/sprites/coin");

	if(sprite == NULL) 
	{
		std::cout << "Failed to find sprite" << std::endl;
	}

	int xpos = x - 5 + (std::rand() % 25);
	int ypos = y - 5 + (std::rand() % 25);

	bbox = std::make_shared<SFBoundingBox>(Point2(xpos, ypos), 25, 25);

	frame = std::rand() % 5;
}

void SFParticle::Render() 
{
	SDL_Rect rect = bbox->GetBox();
	SDL_RenderCopy(sfwindow->getRenderer(), sprite, NULL, &rect);
	frame++;
}

bool SFParticle::IsDead() { return frame > 10; }
