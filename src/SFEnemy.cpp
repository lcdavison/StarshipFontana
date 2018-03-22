#include "SFEnemy.h"

SFEnemy::SFEnemy(const SFASSETTYPE assetType, const std::shared_ptr<SFWindow> window, const SFENEMYTYPE enemyType) : SFAsset(assetType, window) {
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

void SFEnemy::TakeDamage(short damage) {
	health -= damage;
}

short SFEnemy::GetHealth() {
	return health;
}

bool SFEnemy::IsDead() {
	return health <= 0;
}

void SFEnemy::Move() {
	//	TODO:	Make the enemy automatically move around the screen
}
