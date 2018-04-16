#include "SFProjectile.h"

SFProjectile::SFProjectile(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window, PROJECTILE_TYPE projectile_type) : SFAsset(name, type, window) {
	projectile = projectile_type;

	SetupSprite();
	lifetime = 1000;
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

void SFProjectile::OnUpdate() {
	GoNorth();

	for(auto a : SFAssetManager::FindAssetsOfType<SFEnemy>(SFASSET_ALIEN)) {

		if(CollidesWith(a)) {
			a->TakeDamage(GetDamage());

			HandleCollision();

			if(a->IsDead()) {
				a->HandleCollision();
				SFAssetManager::SpawnAtPosition<SFCoin>(std::make_shared<SFCoin>("coin", SFASSET_COIN, sf_window), a->GetPosition());
			}
		}
	}


	lifetime -= 10;

	if(IsOutsideWindow() || lifetime == 0) SetNotAlive();
}

void SFProjectile::SetDamage(short amount) {
	damage = amount;
}

short SFProjectile::GetDamage() {
	return damage;
}
