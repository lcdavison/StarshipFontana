#include "SFEnemy.h"

SFEnemy::SFEnemy(std::string name, SFASSETTYPE assetType, std::shared_ptr<SFWindow> window, SFENEMYTYPE enemyType) : SFAsset(name, assetType, window) {

	SetupSprite();

	type = enemyType;
	movement_direction = LEFT;

	switch(type) {
		case GRUNT:
			health = 50;
			break;
		case BRAWLER:
			health = 100;
			break;
		case ELITE:
			health = 150;
			break;
		case BOSS:
			health = 200;
			break;
	}
	
	player = SFAssetManager::FindAssetByName<SFPlayer>("player");	
}

void SFEnemy::SetupSprite() {
	sprite = IMG_LoadTexture(sf_window->getRenderer(), "assets/sprites/alien.png");

	int w, h;
	SDL_QueryTexture(sprite, NULL, NULL, &w, &h);

	bbox = make_shared<SFBoundingBox>(Point2(0.0f, 0.0f), w , h);
}

void SFEnemy::OnUpdate() {
	//MoveAround();
	
	if(CollidesWith(player)) {
		player->TakeDamage(20);
		HandleCollision();
		SFAssetManager::SpawnAtPosition(std::make_shared<SFCoin>("coin", SFASSET_COIN, sf_window), GetPosition());
	}

	//	Get Player From Asset Manager
	/*	if(CollidesWith()) {
		player->TakeDamage(20);
		HandleCollision();
		SpawnCoin();	//	Should Go in Asset Manager When Ready, but something like CreateAsset();
		}*/
}

void SFEnemy::TakeDamage(short damage) { health -= damage; }

short SFEnemy::GetHealth() { return health; }

bool SFEnemy::IsDead() { return health <= 0; }

void SFEnemy::MoveAround() {

	//	1.	Get Current Plane Position
	Point2 currentPosition = GetPosition();

	//	2.	Perform Movement Checks
	if(currentPosition.getX() <= 0)
		movement_direction = RIGHT;
	else if(currentPosition.getX() >= sf_window->GetWidth() - bbox->GetWidth())
		movement_direction = LEFT;

	//	3.	Move
	switch(movement_direction) {
		case RIGHT:
			GoEast();
			break;
		case LEFT:
			GoWest();
			break;
	}
}

void SFEnemy::GoEast() {
	Vector2 v = Vector2(0.5f, 0.0f) * movement_speed;
	bbox->Translate(v);
}

void SFEnemy::GoWest() {
	Vector2 v = Vector2(-0.5f, 0.0f) * movement_speed;
	bbox->Translate(v);
}

/*void SFEnemy::MoveTowards(const std::shared_ptr<SFAsset> other) {

	float distance;	

	if(!isMoving) {

		end_point = make_shared<Point2>(other->GetCenter());

		if(GetPosition().getX() == end_point->getX() && GetPosition().getY() == end_point->getY())
			return;

		initial_distance = GetPosition().DistanceTo(*end_point);

		Vector2 direction = *end_point - GetPosition();

		float move_x;
		float move_y;

		if(direction.getX() < 0) move_x = 1;
		else move_x = -1;

		if(direction.getY() < 0) move_y = 1;
		else move_y = -1;

		move_direction = std::make_shared<Vector2>(Vector2(move_x, move_y) * movement_speed); 

		isMoving = true;
	} else {
		distance = GetPosition().DistanceTo(*end_point);
	}

	if(distance > initial_distance) bbox->Translate(*move_direction);
	else isMoving = false; 
}*/
