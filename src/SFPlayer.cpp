#include "SFPlayer.h"

SFPlayer::SFPlayer(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window) : SFAsset (name, type, window) {
	SetupSprite("assets/sprites/player.png");
	std::shared_ptr<SFPlayer> player (this);
	smoke_emitter = std::make_shared<SFParticleEmitter>(std::dynamic_pointer_cast<SFAsset>(player), 30, window);
}

void SFPlayer::OnUpdate() {
	if(health < 40)
		smoke_emitter->Emit();

	if(IsDead()) {
		alive = false;
	}
}

void SFPlayer::OnRender() {
	SFAsset::OnRender();	//	Run render code from parent class

	if(health <= 40)
		smoke_emitter->OnRender();
}

void SFPlayer::GoNorth() {
	Vector2 v = Vector2(0.0f, -5.0f) * movement_speed;
	if(GetPosition().getY() >= 0) bbox->Translate(v);
	
	CheckCollision(v);
}

void SFPlayer::GoSouth() {
	Vector2 v = Vector2(0.0f, 5.0f) * movement_speed;
	if(GetPosition().getY() <= sf_window->GetHeight() - bbox->GetHeight()) bbox->Translate(v);
	
	CheckCollision(v);
}

void SFPlayer::GoEast() {
	Vector2 v = Vector2(5.0f, 0.0f) * movement_speed;
	if(GetPosition().getX() <= sf_window->GetWidth() - bbox->GetWidth())	bbox->Translate(v);
	
	CheckCollision(v);
}

void SFPlayer::GoWest() {
	Vector2 v = Vector2(-5.0f, 0.0f) * movement_speed;
	if(GetPosition().getX() > 0) bbox->Translate(v);
	
	CheckCollision(v);
}

void SFPlayer::CheckCollision(Vector2& direction) {
	for(auto wall : SFAssetManager::GetAssetsOfType<SFObstacle>(SFASSET_OBSTACLE)) {
		if(CollidesWith(wall)) {
			has_collision = true;
		}
	}

	if(has_collision) {
		direction = direction * -1;
		bbox->Translate(direction);
		has_collision = false;
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
