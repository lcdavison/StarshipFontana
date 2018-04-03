#include "SFProjectile.h"

SFProjectile::SFProjectile(const SFASSETTYPE type, const std::shared_ptr<SFWindow> window, const PROJECTILE_TYPE projectile_type) : SFAsset(type, window) {
	projectile = projectile_type;

	SetupSprite();
}

void SFProjectile::SetupSprite() {

	switch(projectile) {
		case BULLET:
			sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/projectile.png");
			break;
		case ROCKET:
			break;
	}

	int w, h;
	SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w, h);

}

void SFProjectile::SetDamage(short amount) {
	damage = amount;
}

short SFProjectile::GetDamage() {
	return damage;
}
