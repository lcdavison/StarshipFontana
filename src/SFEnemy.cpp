#include "SFEnemy.h"

SFEnemy::SFEnemy(std::string name, 
				 SFASSETTYPE assetType, 
				 std::shared_ptr<SFWindow> window) 
				 : SFAsset(name, assetType, window) 
{
	SetupSprite("assets/sprites/alien.png");

	health = 100;
	movement_direction = LEFT;
	
	player = SFAssetManager::GetAssetByName<SFPlayer>("player");	

	SetMovementSpeed(0.2f);
}

//
//	OnUpdate
//		Custom update behaviour
//
void SFEnemy::OnUpdate() 
{
	MoveAround();
	Attack();

	if(CollidesWith(player)) 
	{
		player->TakeDamage(20);
		HandleCollision();
	}
}

//	
//	TakeDamage
//		Deducts damage from health
//
void SFEnemy::TakeDamage(short damage) 
{ 
	health -= damage; 
}

//	
//	GetHealth
//		Returns enemy health
//
short SFEnemy::GetHealth() 
{ 
	return health; 
}

//	
//	IsDead
//		Determines if enemy is dead
//
bool SFEnemy::IsDead() 
{ 
	return health <= 0; 
}

//	
//	MoveAround
//		Moves the enemy each frame
//
void SFEnemy::MoveAround() 
{
	//	1.	Get Current Position
	Point2 currentPosition = GetPosition();

	//	2.	Perform Movement Checks
	if(currentPosition.getX() <= 0) 
	{
		movement_direction = RIGHT;
		GoSouth();
	} 
	else if(currentPosition.getX() >= sf_window->GetWidth() - bbox->GetWidth()) 
	{
		movement_direction = LEFT;
		GoSouth();
	}

	//	3.	Move
	switch(movement_direction) 
	{
		case RIGHT:
			GoEast();
			break;

		case LEFT:
			GoWest();
			break;
	}
}

//	
//	Attack
//		Causes the enemy to fire projectiles
//
void SFEnemy::Attack() 
{
	attack_interval++;

	if(attack_interval >= 150) 
	{
		std::shared_ptr<SFProjectile> projectile = std::make_shared<SFProjectile>("projectile", 
																				  SFASSET_PROJECTILE, 
																				  sf_window, 
																				  BULLET, 
																				  SOUTH);
		projectile->SetDamage(10);

		auto v = GetCenter();
		auto pos = Point2(v.getX() - projectile->GetBoundingBox()->GetWidth() / 2, 
						  v.getY() + GetBoundingBox()->GetHeight());

		projectile->SetPosition(pos);

		SFAssetManager::AddAsset<SFProjectile>(projectile);
		attack_interval = 0;
	}
}
