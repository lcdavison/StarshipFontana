#include "SFApp.h"

// TODO: Vary the enemy types when starting the level.
// TODO: Add Game states or potentially scenes to determine what should be drawn

SFApp::SFApp(std::shared_ptr<SFWindow> window) : is_running(true), window(window) {
	int canvas_w = window->GetWidth();
	int canvas_h = window->GetHeight();

	player = make_shared<SFPlayer>(SFASSET_PLAYER, window);
	auto player_pos = Point2(canvas_w / 2 - player->GetBoundingBox()->GetWidth() / 2, canvas_h - player->GetBoundingBox()->GetHeight());
	player->SetPosition(player_pos);

	const int number_of_aliens = 10;
	enemies_remaining = number_of_aliens;
	for (int i = 0; i < number_of_aliens; i++) {
		// place an alien at width/number_of_aliens * i
		auto alien = make_shared<SFEnemy>(SFASSET_ALIEN, window, ELITE);
		auto pos = Point2((canvas_w / number_of_aliens) * i + alien->GetBoundingBox()->GetWidth() / 2, 200.0f);
		alien->SetPosition(pos);
		aliens.push_back(alien);
	}

	auto coin = make_shared<SFCoin>(SFASSET_COIN, window);
	auto pos = Point2((canvas_w / 4), 100);
	coin->SetPosition(pos);
	coins.push_back(coin);
}

SFApp::~SFApp() {}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
	SFEVENT the_event = event.GetCode();
	switch (the_event) {
		case SFEVENT_QUIT:
			is_running = false;
			break;
		case SFEVENT_UPDATE:
			OnUpdate();
			OnRender();
			break;
		case SFEVENT_PLAYER_LEFT:
			player->GoWest();
			break;
		case SFEVENT_PLAYER_RIGHT:
			player->GoEast();
			break;
		case SFEVENT_PLAYER_UP:
			player->GoNorth();
			break;
		case SFEVENT_PLAYER_DOWN:
			player->GoSouth();
			break;
		case SFEVENT_FIRE:	
			FireProjectile();
			break;
	}
}

void SFApp::StartMainLoop() {
	SDL_Event event;
	while (SDL_WaitEvent(&event) && is_running) {

		// wrap an SDL_Event with our SFEvent
		SFEvent sfevent((const SDL_Event)event);

		// handle our SFEvent
		OnEvent(sfevent);
	}
}

void SFApp::OnUpdate() {

	// 1. Move / update game objects
	for (auto p : projectiles) {
		p->GoNorth();
	}

	// coins
	for (auto c : coins) {
		if(c->CollidesWith(player)) {
			player->AddCoin();
			c->SetNotAlive();	
		}
	}

	// enemies
	for (auto a : aliens) {

		//a->MoveTowards(player);

		if(a->CollidesWith(player)) {
			player->TakeDamage(20);
			a->SetNotAlive();
		}
	}

	// 2. Detect collisions
	for (auto p : projectiles) {
		for (auto a : aliens) {
			if (p->CollidesWith(a)) {

				a->TakeDamage(p->GetDamage());

				p->HandleCollision();

				if(a->IsDead()) { 
					a->HandleCollision();
					enemies_remaining--;
					SpawnCoin(a->GetPosition());
				}
			}
		}
	}

	// Remove projectiles
	ClearProjectiles();

	// 3. Remove dead aliens
	ClearDeadAliens();

	//Remove collected coins
	ClearDeadCoins();
}

void SFApp::OnRender() {

	// 1. Clear visible content
	window->ClearScreen();

	//	Draw HUD
	DrawHUD();

	// 2. Draw game objects off-screen
	player->OnRender();

	for (auto p : projectiles) {
		if (p->IsAlive()) { 
			p->OnRender(); 
		}
	}

	for (auto a : aliens) {
		if (a->IsAlive()) { 
			a->OnRender(); 
		}
	}

	for (auto c : coins) {
		if(c->IsAlive()) {
			c->OnRender();
		}
	}

	// 3. Switch the off-screen buffer to be on-screen
	window->ShowScreen();
}

void SFApp::FireProjectile() {
	shared_ptr<SFProjectile> bullet = make_shared<SFProjectile>(SFASSET_PROJECTILE, window, BULLET);

	bullet->SetDamage(player->GetDamage());

	auto v = player->GetCenter(); 
	auto pos = Point2(v.getX() - bullet->GetBoundingBox()->GetWidth() / 2, v.getY());
	bullet->SetPosition(pos);
	projectiles.push_back(bullet);
}

//	TODO: Move Draw HUD to the window
void SFApp::DrawHUD() {
	SDL_Color textColour = { 0, 255, 0, 255 };

	std::string healthText = "HEALTH : " + std::to_string(player->GetHealth());
	std::string enemies_remainingText = "ENEMIES : " + std::to_string(enemies_remaining);
	std::string coinText = "COINS : " + std::to_string(player->GetCoins());

	SF_UILabel::DrawText(healthText, window->GetWidth() / 2, 0, textColour, window);
	SF_UILabel::DrawText(enemies_remainingText, 0, 0, textColour, window);
	SF_UILabel::DrawText(coinText, 10, 30, textColour, window);	
}

void SFApp::SpawnCoin(Point2 position) {
	auto coin = make_shared<SFCoin>	(SFASSET_COIN, window);
	coin->SetPosition(position);
	coins.push_back(coin);
}

void SFApp::ClearDeadCoins() {
	coins.remove_if([](shared_ptr<SFCoin> coin) { return !coin->IsAlive(); });
}

void SFApp::ClearDeadAliens() {
	aliens.remove_if([](shared_ptr<SFEnemy> alien) { return !alien->IsAlive(); });
}

void SFApp::ClearProjectiles() {
	projectiles.remove_if([](shared_ptr<SFProjectile> projectile) { return !projectile->IsAlive(); });
}

shared_ptr<SFPlayer> SFApp::GetPlayer() { return player; }
