#include "SFCoin.h"

SFCoin::SFCoin(std::string name, SFASSETTYPE type, std::shared_ptr<SFWindow> window) : SFAsset(name, type, window) { 
	SetupSprite("assets/sprites/coin.png");

	player = SFAssetManager::FindAssetByName<SFPlayer>("player");

	movement_speed = 3.0f;
}

void SFCoin::OnUpdate() {
	if(CollidesWith(player)) {
		player->AddCoin();
		SetNotAlive();
	}

	if(DistanceTo(player) < 200.0f) {
//		MoveTowards(player);
	
		Lerp(player, 0.01f);
	}
}
