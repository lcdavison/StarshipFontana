#include "SFParticle.h"

// TODO: Add Alpha Blending

SFParticle::SFParticle(int x, int y, std::shared_ptr<SFWindow> window) : sfwindow(window) {
	sprite = IMG_LoadTexture(sfwindow->getRenderer(), "assets/sprites/smoke.png");

	if(sprite == NULL) 
		std::cout << "Failed to find sprite" << std::endl;

	bbox = std::make_shared<SFBoundingBox>(Point2(x, y), 10, 10);

	frame = std::rand() % 5;
}

void SFParticle::OnUpdate() {
	float angle_degrees = atan2(bbox->GetX(), bbox->GetY()) * 180 / M_PI * std::rand();

	int x = bbox->GetX() + cos(angle_degrees) * 0.02f;
	int y = bbox->GetY() + sin(angle_degrees) * -0.02f;

	Point2 pos = Point2(x, y);
	bbox->SetPosition(pos);
}

void SFParticle::OnRender() {
	SDL_Rect rect = bbox->GetBox();
	SDL_RenderCopy(sfwindow->getRenderer(), sprite, NULL, &rect);
	frame++;
}

bool SFParticle::IsDead() { return frame > 30; }
