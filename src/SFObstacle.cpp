#include "SFObstacle.h"

SFObstacle::SFObstacle(const std::string name, const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) : SFAsset(name, type, window) {
	// TODO: Setup sprite
	SetupSprite("assets/sprites/coin.png");
}

SFObstacle::~SFObstacle() {
}

void SFObstacle::OnUpdate() {
	// TODO: Check collisions
}
