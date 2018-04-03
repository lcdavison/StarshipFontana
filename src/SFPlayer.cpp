#include "SFPlayer.h"

SFPlayer::SFPlayer(const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) : SFAsset (type, window) {
	SetupSprite();
}

void SFPlayer::SetupSprite() {
	sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/player.png");

	int w, h;
	SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w, h);
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
