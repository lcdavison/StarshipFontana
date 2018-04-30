#ifndef SFPLAYER_H
#define SFPLAYER_H

#include "SFAssetManager.h"

class SFPlayer : public SFAsset {
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

		void GoNorth();
		void GoSouth();
		void GoEast();
		void GoWest();

		void CheckCollision();
	private:
		short coins = 0;
		short health = 100;
		short damage = 25;
};                               
#endif                           

