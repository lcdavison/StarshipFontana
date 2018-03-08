#include "SFPlayer.h"

SFPlayer::SFPlayer(const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) : SFAsset (type, window) { }

void SFPlayer::AddCoin() {
	Coins++;
}

short SFPlayer::GetCoins() {
	return Coins;
}

void SFPlayer::TakeDamage(short damage) {
	Health -= damage;
}

short SFPlayer::GetHealth() {
	return Health;
}
