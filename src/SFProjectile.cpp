#include "SFProjectile.h"

SFProjectile::SFProjectile(const SFASSETTYPE type, const std::shared_ptr<SFWindow> window) : SFAsset(type, window) { }

void SFProjectile::SetDamage(short amount) {
	damage = amount;
}

short SFProjectile::GetDamage() {
	return damage;
}
