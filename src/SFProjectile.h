#ifndef SFPROJECTILE_H
#define SFPROJECTILE_H

#include "SFAssetManager.h"

enum SFPROJECTILETYPE { BULLET, ROCKET };

class SFProjectile : public SFAsset {
	public:
		SFProjectile(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>, const SFPROJECTILETYPE);

		void OnUpdate();

		void SetDamage(short);
		short GetDamage();
	private:
	//	float projectile_speed = 1.0f;
		short damage;
		SFPROJECTILETYPE projectile;
};
#endif
