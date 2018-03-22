#include "SFPlayer.h"

SFPlayer::SFPlayer(const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) : SFAsset (type, window) { }

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
