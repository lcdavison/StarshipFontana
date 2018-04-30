#ifndef SFPROJECTILE_H
#define SFPROJECTILE_H

#include "SFAssetManager.h"

enum SFPROJECTILE_TYPE { BULLET, ROCKET };
enum SFPROJECTILE_DIRECTION { NORTH, SOUTH };

class SFProjectile : public SFAsset {
	public:
		SFProjectile(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>, const SFPROJECTILE_TYPE, const SFPROJECTILE_DIRECTION);

		void OnUpdate();

		void SetDamage(short);
		short GetDamage();
	private:
		short damage;
		SFPROJECTILE_TYPE projectile;
		SFPROJECTILE_DIRECTION direction;
};
#endif
