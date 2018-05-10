#ifndef SFENEMY_H
#define SFENEMY_H

#include "SFAssetManager.h"
#include "SFParticleEmitter.h"

class SFPlayer;

class SFEnemy : public SFAsset 
{
	public:

		SFEnemy(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);

		void 					OnUpdate();
		void					OnRender();

		/*---HEALTH---*/
		bool 					IsDead();
		void 					TakeDamage(short);
		short 					GetHealth();

	private:

		enum SFENEMYDIRECTION { LEFT, RIGHT };

		SFENEMYDIRECTION 			movement_direction;

		void 					MoveAround();
		void 					Attack();

		int	 				attack_interval = 0;
		short 					health;
		
		std::shared_ptr<SFParticleEmitter> 	smoke_emitter;
		std::shared_ptr<SFPlayer> 		player;

};                                                                        
#endif                               	
