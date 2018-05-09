#ifndef SFPROJECTILE_H
#define SFPROJECTILE_H

#include "SFAssetManager.h"

enum SFPROJECTILE_DIRECTION { NORTH, SOUTH };

class SFProjectile : public SFAsset 
{
	public:

		SFProjectile(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>, const SFPROJECTILE_DIRECTION);

		void 						OnUpdate();

		void 						SetDamage(short);
		short 						GetDamage();

	private:

		void 						Move();

		short 						damage;
		SFPROJECTILE_DIRECTION 		direction;
		std::shared_ptr<SFPlayer> 	player;

};
#endif
