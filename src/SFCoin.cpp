#include "SFCoin.h"

SFCoin::SFCoin(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window) : SFAsset(name, type, window) { 
	SetupSprite();
}


void SFCoin::SetupSprite() {

	sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/coin.png");

	if(!sprite)
		throw SFException("Sprite Not Found");

	int w, h;
	SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w, h);
}

void SFCoin::OnUpdate() {
}
