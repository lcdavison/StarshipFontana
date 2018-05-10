#include "SFProjectile.h"

SFProjectile::SFProjectile(std::string name,
			   SFASSETTYPE type,
			   std::shared_ptr<SFWindow> window,
			   SFPROJECTILE_DIRECTION proj_direction)
			   : SFAsset(name, type, window) 
{
	direction = proj_direction;

	SetupSprite("assets/sprites/projectile.png");

	player = SFAssetManager::GetAssetByName<SFPlayer>("player");
	lifetime = 1000;
}

/*
	OnUpdate
		Custom update behaviour
*/
void SFProjectile::OnUpdate() 
{
	Move();

	for(auto enemy : SFAssetManager::GetAssetsOfType<SFEnemy>(SFASSET_ENEMY)) 
	{
		if(CollidesWith(enemy)) 
		{
			enemy->TakeDamage(GetDamage());

			HandleCollision();

			if(enemy->IsDead()) 
			{
				enemy->HandleCollision();
				SFAssetManager::SpawnAtPosition<SFCoin>(std::make_shared<SFCoin>("coin", SFASSET_COIN, sf_window),
									enemy->GetPosition());
			}
		}
	}

	for(auto wall : SFAssetManager::GetAssetsOfType<SFObstacle>(SFASSET_OBSTACLE)) 
	{
		if(CollidesWith(wall)) 
		{
			wall->TakeDamage(GetDamage());
			HandleCollision();
		}
	}

	if(CollidesWith(player)) 
	{
		player->TakeDamage(GetDamage());
		HandleCollision();
	}

	lifetime -= 10;

	if(IsOutsideWindow() 
	   || lifetime == 0) 
	   SetNotAlive();
}

/*
	Move
		Moves projectile in direction
*/
void SFProjectile::Move() 
{
	switch(direction) 
	{
		case NORTH:
			GoNorth();
			break;

		case SOUTH:
			GoSouth();
			break;
	}
}

/*
	SetDamage
		Sets the projectiles damage amount
*/
void SFProjectile::SetDamage(short amount) 
{
	damage = amount;
}

/*
	GetDamage
		Returns the projectiles damage
*/
short SFProjectile::GetDamage() 
{
	return damage;
}
