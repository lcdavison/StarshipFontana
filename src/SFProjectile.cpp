#include "SFProjectile.h"

SFProjectile::SFProjectile(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window, SFPROJECTILETYPE projectile_type) : SFAsset(name, type, window) {
	projectile = projectile_type;

	SetupSprite("assets/sprites/projectile.png");

	/*switch(projectile) {
		case BULLET:
			sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/projectile.png");
			break;
		case ROCKET:
			break;
	}*/ 

	lifetime = 1000;
}

void SFProjectile::OnUpdate() {
	GoNorth();

	for(auto alien : SFAssetManager::GetAssetsOfType<SFEnemy>(SFASSET_ALIEN)) {

		if(CollidesWith(alien)) {
			alien->TakeDamage(GetDamage());

			HandleCollision();

			if(alien->IsDead()) {
				alien->HandleCollision();
				SFAssetManager::SpawnAtPosition<SFCoin>(std::make_shared<SFCoin>("coin", SFASSET_COIN, sf_window), alien->GetPosition());
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
