#ifndef SFENEMY_H
#define SFENEMY_H

#include "SFAsset.h"

enum SFENEMYTYPE { GRUNT, BRAWLER, ELITE, BOSS };

class SFEnemy : public SFAsset {

	public:
		SFEnemy(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>, const SFENEMYTYPE);

		void Update();

		//	Enemy Health
		bool IsDead();
		void TakeDamage(short);
		short GetHealth();

		//	Enemy Movement
		void MoveAround();
		void MoveTowards(std::shared_ptr<SFAsset>);
	private:
		//	Enemy Movement
		enum SFEnemyDirection { LEFT, RIGHT };

		void GoEast();
		void GoWest();

		bool isMoving = false;
		float movement_speed = 2.0f;
		SFEnemyDirection movement_direction;

		float initial_distance;
		std::shared_ptr<Vector2> move_direction;
		std::shared_ptr<Point2> end_point;

		//	Texture Setup
		void SetupSprite();

		//	Health
		short health;

		//	Enemy Type
		SFENEMYTYPE type;
};                                                                        
#endif                               	
