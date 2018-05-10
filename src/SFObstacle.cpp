#include "SFObstacle.h"

SFObstacle::SFObstacle(const std::string name,
		       const SFASSETTYPE type,
		       const std::shared_ptr<SFWindow> window)
  		       : SFAsset(name, type, window) 
{
	SetupSprite("assets/sprites/barrier.png");
}

/*
  	OnUpdate
  		Custom update behaviour
 */
void SFObstacle::OnUpdate() 
{
	if(IsDead()) 
	{
		SetNotAlive();
	}
}

/*
  	IsDead
  		Determines whether obstacle is dead
 */
bool SFObstacle::IsDead() 
{
	return health <= 0;
}

/*
  	TakeDamage
  		Reduces health by amount
 */
void SFObstacle::TakeDamage(int amount) 
{
	health -= amount;
}
