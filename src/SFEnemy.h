#ifndef SFENEMY_H
#define SFENEMY_H

#include "SFAssetManager.h"

class SFPlayer;

enum SFENEMYTYPE { GRUNT, BRAWLER, ELITE, BOSS };

class SFEnemy : public SFAsset {
	public:
		SFEnemy(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>, const SFENEMYTYPE);

		void OnUpdate();

		//	Enemy Health
		bool IsDead();
		void TakeDamage(short);
		short GetHealth();

	private:
		/*---ENEMY BEHAVIOUR---*/
		enum SFENEMYDIRECTION { LEFT, RIGHT };
		SFENEMYDIRECTION movement_direction;

		void MoveAround();
		void Attack();

		int attack_interval = 0;

		//	Health
		short health;

		//	Enemy Type
		SFENEMYTYPE type;

		//	Asset Pointers
		std::shared_ptr<SFPlayer> player;
};                                                                        
#endif                               	
