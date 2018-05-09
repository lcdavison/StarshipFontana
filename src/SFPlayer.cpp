#include "SFPlayer.h"

SFPlayer::SFPlayer(std::string name,
	   			   SFASSETTYPE type, 
				   std::shared_ptr<SFWindow> window) 
				   : SFAsset (name, type, window) 
{
	SetupSprite("assets/sprites/player.png");

	smoke_emitter = std::make_shared<SFParticleEmitter>(30, 150, window);
}

/*
	OnUpdate
		Custom update behaviour
*/
void SFPlayer::OnUpdate() 
{
	if(health <= 40)
	   smoke_emitter->Emit(GetCenter());

	if(IsDead()) 
	   alive = false;

	if(attack_interval >= 5)
	   attack_interval = 0;

	attack_interval++;	
}

/*
	OnRender
		Custom render behaviour
*/
void SFPlayer::OnRender() 
{
	//	Run render code from parent class
	SFAsset::OnRender();	

	if(health <= 40)
	   smoke_emitter->OnRender();
}

/*
	GoNorth
		Moves the player up
		Checks for collisions
*/
void SFPlayer::GoNorth() 
{
	Vector2 v = Vector2(0.0f, -5.0f) * movement_speed;
	if(GetPosition().getY() >= 0) bbox->Translate(v);
	
	CheckCollision(v);
}

/*
	GoSouth
		Moves the player down
		Checks for collisions
*/
void SFPlayer::GoSouth() 
{
	Vector2 v = Vector2(0.0f, 5.0f) * movement_speed;
	if(GetPosition().getY() <= sf_window->GetHeight() - bbox->GetHeight()) bbox->Translate(v);
	
	CheckCollision(v);
}

/*
	GoEast
		Moves the player right
		Checks for collisions
*/
void SFPlayer::GoEast() 
{
	Vector2 v = Vector2(5.0f, 0.0f) * movement_speed;
	if(GetPosition().getX() <= sf_window->GetWidth() - bbox->GetWidth()) bbox->Translate(v);
	
	CheckCollision(v);
}

/*
	GoWest
		Moves the player left
		Checks for collisions
*/
void SFPlayer::GoWest() 
{
	Vector2 v = Vector2(-5.0f, 0.0f) * movement_speed;
	if(GetPosition().getX() > 0) bbox->Translate(v);
	
	CheckCollision(v);
}

/*
	CheckCollision
		Checks for a collision in given direction
*/
void SFPlayer::CheckCollision(Vector2& direction) 
{
	for(auto wall : SFAssetManager::GetAssetsOfType<SFObstacle>(SFASSET_OBSTACLE)) 
	{
		if(CollidesWith(wall)) 
		   has_collision = true;
	}

	if(has_collision) 
	{
		direction = direction * -1;
		bbox->Translate(direction);
		has_collision = false;
	}
}

/*
	AddCoin
		Adds a single coin to the players collection
*/
void SFPlayer::AddCoin() 
{
	++coins;
}

/*
	GetCoins
		Returns the number of collected coins
*/
short SFPlayer::GetCoins() 
{
	return coins;
}

/*
	TakeDamage
		Reduces health by damage amount
*/
void SFPlayer::TakeDamage(short damage) 
{
	health -= damage;
}

/*
	GetHealth
		Returns current health value
*/
short SFPlayer::GetHealth() 
{
	return health;
}

/*
	IsDead
		Determines if the player is dead
*/
bool SFPlayer::IsDead() 
{
	return health <= 0;
}

/*
	GetDamage
		Returns players damage value
*/
short SFPlayer::GetDamage() 
{
	return damage;
}

/*
  	CanAttack
		Determines whether player can attack
 */ 	
bool SFPlayer::CanAttack() 
{
	return attack_interval >= 5;
}
