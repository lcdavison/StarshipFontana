#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>

#include "SFAsset.h"

class SFPlayer: public SFAsset {

private:
	short Coins;
	short Health = 100;
public:
	SFPlayer(const SFASSETTYPE, const std::shared_ptr<SFWindow>);
	
	//	Player's Coins
	void AddCoin();
	short GetCoins();

	//	Player's Health
	void TakeDamage(short);
	short GetHealth();
};

#endif
