#include "SFEnemy.h"

SFEnemy::SFEnemy(const SFASSETTYPE assetType, const std::shared_ptr<SFWindow> window, const SFENEMYTYPE enemyType) : SFAsset(assetType, window) {

	SetupSprite();

	type = enemyType;
	
	switch(type) {
	case GRUNT:
		health = 50;
		break;
	case BRAWLER:
		health = 100;
		break;
	case ELITE:
		health = 150;
		break;
	case BOSS:
		health = 200;
		break;
	}
}

void SFEnemy::SetupSprite() {
	sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/alien.png");

	int w, h;
	SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w , h);
}

void SFEnemy::TakeDamage(short damage) { health -= damage; }

short SFEnemy::GetHealth() { return health; }

bool SFEnemy::IsDead() { return health <= 0; }

void SFEnemy::MoveTowards(std::shared_ptr<SFAsset> other) {
	//	TODO:	Make the enemy automatically move around the screen	

	float distance = Point2::Distance(GetPosition(), other->GetPosition());

	if(distance > 5.0f)
		GoSouth();
}
