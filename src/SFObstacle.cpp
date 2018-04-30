#include "SFObstacle.h"

SFObstacle::SFObstacle(const std::string name, const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) : SFAsset(name, type, window) {
	SetupSprite("assets/sprites/barrier.png");
}
