#ifndef SFPLAYER_H
#define SFPLAYER_H

#include "SFAssetManager.h"
#include "SFParticleEmitter.h"

class SFPlayer : public SFAsset 
{
	public:

		SFPlayer(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);

		void 								OnUpdate();
		void 								OnRender();

		void 								AddCoin();
		short 								GetCoins();

		void 								TakeDamage(short);
		short 								GetHealth();
		bool 								IsDead();

		short 								GetDamage();

		void 								GoNorth();
		void 								GoSouth();
		void 								GoEast();
		void 								GoWest();

		void 								CheckCollision(Vector2&);

	private:

		short 								coins = 0;
		short 								health = 100;
		short 								damage = 25;

		std::shared_ptr<SFParticleEmitter>	smoke_emitter;

};                               
#endif                           

