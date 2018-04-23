#include "SFPlayer.h"

SFPlayer::SFPlayer(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window) : SFAsset (name, type, window) {
	SetupSprite("assets/sprites/player.png");
}

void SFPlayer::OnUpdate() {
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
