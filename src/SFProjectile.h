#ifndef SFPROJECTILE_H
#define SFPROJECTILE_H

#include "SFAsset.h"

class SFProjectile : public SFAsset {
	
public:
	SFProjectile(const SFASSETTYPE, const std::shared_ptr<SFWindow>);
	void SetDamage(short);
	short GetDamage();

	float ProjectileSpeed = 1.0f;

private:
	short damage;
};

#endif
