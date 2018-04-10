#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>

#include "SFAsset.h"

class SFPlayer: public SFAsset {

private:
	short coins = 0;
	short health = 100;
	short damage = 25;

	void SetupSprite();
public:
	SFPlayer(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);

	void OnUpdate();
	
	//	Player's Coins
	void AddCoin();
	short GetCoins();

	//	Player's Health
	void TakeDamage(short);
	short GetHealth();
	bool IsDead();

	//	Player Damage
	short GetDamage();
	void ModifyDamage(short);
};
#endif
