#ifndef SFENEMY_H
#define SFENEMY_H

#include "SFAsset.h"

enum SFENEMYTYPE { GRUNT, BRAWLER, ELITE, BOSS };

class SFEnemy : public SFAsset {

public:
	SFEnemy(const SFASSETTYPE, const std::shared_ptr<SFWindow>, const SFENEMYTYPE);
	
	//	Enemy Health
	bool IsDead();
	void TakeDamage(short);
	short GetHealth();

	//	Enemy Movement
	void Move();

	//	Distance To Player
	float DistanceToAsset(std::shared_ptr<SFAsset>);
private:
	void SetupSprite();

	short health;
	SFENEMYTYPE type;
};                                                                        
#endif                               	
