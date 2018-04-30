#include "SFPlayer.h"

SFPlayer::SFPlayer(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window) : SFAsset (name, type, window) {
	SetupSprite("assets/sprites/player.png");
}

void SFPlayer::OnUpdate() {
	if(IsDead()) {
		alive = false;
	}
}

void SFPlayer::GoNorth() {
	Vector2 v = Vector2(0.0f, -5.0f) * movement_speed;
	bbox->Translate(v);
	
	CheckCollision();

	if(has_collision) {
		v = v * -1;
		bbox->Translate(v);
		has_collision = false;
	}
}

void SFPlayer::GoSouth() {
	Vector2 v = Vector2(0.0f, 5.0f) * movement_speed;
	bbox->Translate(v);
	
	CheckCollision();

	if(has_collision) {
		v = v * -1;
		bbox->Translate(v);
		has_collision = false;
	}
}

void SFPlayer::GoEast() {
	Vector2 v = Vector2(5.0f, 0.0f) * movement_speed;
	if(GetPosition().getX() <= sf_window->GetWidth() - bbox->GetWidth())	bbox->Translate(v);
	
	CheckCollision();

	if(has_collision) {
		v = v * -1;
		bbox->Translate(v);
		has_collision = false;
	}
}

void SFPlayer::GoWest() {
	Vector2 v = Vector2(-5.0f, 0.0f) * movement_speed;
	if(GetPosition().getX() > 0) bbox->Translate(v);
	
	CheckCollision();

	if(has_collision) {
		v = v * -1;
		bbox->Translate(v);
		has_collision = false;
	}
}

void SFPlayer::CheckCollision() {
	for(auto wall : SFAssetManager::GetAssetsOfType<SFObstacle>(SFASSET_OBSTACLE)) {
		if(CollidesWith(wall)) {
			has_collision = true;
		}
	}
}

void SFPlayer::AddCoin() {
	coins++;
}

short SFPlayer::GetCoins() {
	return coins;
}

void SFPlayer::TakeDamage(short damage) {
	health -= damage;
}

short SFPlayer::GetHealth() {
	return health;
}

bool SFPlayer::IsDead() {
	return health <= 0;
}

short SFPlayer::GetDamage() {
	return damage;
}

void SFPlayer::ModifyDamage(short modifier) {
	damage += modifier;
}
