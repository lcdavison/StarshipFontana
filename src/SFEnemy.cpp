#include "SFEnemy.h"

SFEnemy::SFEnemy(std::string name, SFASSETTYPE assetType, std::shared_ptr<SFWindow> window, SFENEMYTYPE enemyType) : SFAsset(name, assetType, window) {

	SetupSprite();

	type = enemyType;
	movement_direction = LEFT;

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
	
	player = SFAssetManager::FindAssetByName<SFPlayer>("player");	
}

void SFEnemy::SetupSprite() {
	sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/alien.png");

	int w, h;
	SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w , h);
}

void SFEnemy::OnUpdate() {
	//MoveAround();
	
	if(CollidesWith(player)) {
		player->TakeDamage(20);
		HandleCollision();
		SFAssetManager::SpawnAtPosition(std::make_shared<SFCoin>("coin", SFASSET_COIN, sf_window), GetPosition());
	}
}

void SFEnemy::TakeDamage(short damage) { health -= damage; }

short SFEnemy::GetHealth() { return health; }

bool SFEnemy::IsDead() { return health <= 0; }

void SFEnemy::MoveAround() {

	//	1.	Get Current Plane Position
	Point2 currentPosition = GetPosition();

	//	2.	Perform Movement Checks
	if(currentPosition.getX() <= 0)
		movement_direction = RIGHT;
	else if(currentPosition.getX() >= sf_window->GetWidth() - bbox->GetWidth())
		movement_direction = LEFT;

	//	3.	Move
	switch(movement_direction) {
		case RIGHT:
			GoEast();
			break;
		case LEFT:
			GoWest();
			break;
	}
}
