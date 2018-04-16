#ifndef SFENEMY_H
#define SFENEMY_H

#include "SFAssetManager.h"

enum SFENEMYTYPE { GRUNT, BRAWLER, ELITE, BOSS };

class SFEnemy : public SFAsset {

	public:
		SFEnemy(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>, const SFENEMYTYPE);

		void OnUpdate();

		//	Enemy Health
		bool IsDead();
		void TakeDamage(short);
		short GetHealth();

		//	Enemy Movement
		void MoveAround();
	private:
		//	Enemy Movement
		enum SFEnemyDirection { LEFT, RIGHT };

		void GoEast();
		void GoWest();

		SFEnemyDirection movement_direction;

		//	Texture Setup
		void SetupSprite();

		//	Health
		short health;

		//	Enemy Type
		SFENEMYTYPE type;

		std::shared_ptr<SFPlayer> player;
};                                                                        
#endif                               	
