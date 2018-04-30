#include "SFEnemy.h"

SFEnemy::SFEnemy(std::string name, SFASSETTYPE assetType, std::shared_ptr<SFWindow> window, SFENEMYTYPE enemyType) : SFAsset(name, assetType, window) {

	SetupSprite("assets/sprites/alien.png");

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
	
	player = SFAssetManager::GetAssetByName<SFPlayer>("player");	
	SetMovementSpeed(0.2f);
}

void SFEnemy::OnUpdate() {
	MoveAround();
	
	if(CollidesWith(player)) {
		player->TakeDamage(20);
		HandleCollision();
	}
}

void SFEnemy::TakeDamage(short damage) { health -= damage; }

short SFEnemy::GetHealth() { return health; }

bool SFEnemy::IsDead() { return health <= 0; }

void SFEnemy::MoveAround() {

	//	1.	Get Current Plane Position
	Point2 currentPosition = GetPosition();

	//	2.	Perform Movement Checks
	if(currentPosition.getX() <= 0) {
		movement_direction = RIGHT;
		GoSouth();
	} else if(currentPosition.getX() >= sf_window->GetWidth() - bbox->GetWidth()) {
		movement_direction = LEFT;
		GoSouth();
	}

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
