#include "SFProjectile.h"

SFProjectile::SFProjectile(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window, SFPROJECTILE_TYPE proj_type, SFPROJECTILE_DIRECTION proj_direction) : SFAsset(name, type, window) {
	projectile = proj_type;
	direction = proj_direction;

	SetupSprite("assets/sprites/projectile.png");

	/*switch(projectile) {
		case BULLET:
			sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/projectile.png");
			break;
		case ROCKET:
			break;
	}*/ 

	player = SFAssetManager::GetAssetByName<SFPlayer>("player");
	lifetime = 1000;
}

void SFProjectile::OnUpdate() {
	Move();

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

	for(auto wall : SFAssetManager::GetAssetsOfType<SFObstacle>(SFASSET_OBSTACLE)) {
		if(CollidesWith(wall)) {
			HandleCollision();
		}
	}

	if(CollidesWith(player)) {
		player->TakeDamage(GetDamage());
		HandleCollision();
	}

	lifetime -= 10;

	if(IsOutsideWindow() || lifetime == 0) SetNotAlive();
}

void SFProjectile::Move() {
	switch(direction) {
		case NORTH:
			GoNorth();
			break;
		case SOUTH:
			GoSouth();
			break;
	}
}

void SFProjectile::SetDamage(short amount) {
	damage = amount;
}

short SFProjectile::GetDamage() {
	return damage;
}
