#include "SFCoin.h"

SFCoin::SFCoin(std::string name,
	       SFASSETTYPE type,
	       std::shared_ptr<SFWindow> window)
  	       : SFAsset(name, type, window) 
{ 
	SetupSprite("assets/sprites/coin.png");

	player = SFAssetManager::GetAssetByName<SFPlayer>("player");
	
	SetMovementSpeed(3.0f);
}

/*
	OnUpdate
		Updates the coin
*/		
void SFCoin::OnUpdate() 
{
	if(CollidesWith(player)) 
	{
		player->AddCoin();
		SetNotAlive();
	}

	if(DistanceTo(player) < 400.0f) 
	{
		Lerp(player, 0.01f);
	}
}
