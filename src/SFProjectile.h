#ifndef SFPROJECTILE_H
#define SFPROJECTILE_H

#include "SFAssetManager.h"

enum PROJECTILE_TYPE { BULLET, ROCKET };

class SFProjectile : public SFAsset {
	
public:
	SFProjectile(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>, const PROJECTILE_TYPE);

	void OnUpdate();

	void SetDamage(short);
	short GetDamage();

	float ProjectileSpeed = 1.0f;

private:
	short damage;
	PROJECTILE_TYPE projectile;
};
#endif
