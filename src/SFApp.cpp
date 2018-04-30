#include "SFApp.h"

// TODO: Vary the enemy types when starting the level.
// TODO: Adjust OnClick button event trigger 
// TODO: Change the README.md 

SFApp::SFApp(std::shared_ptr<SFWindow> window) : is_running(true), window(window) {
	int canvas_w = window->GetWidth();
	int canvas_h = window->GetHeight();

	SFAssetManager::CreateAsset<SFPlayer>("player", SFASSET_PLAYER, window);
	player = SFAssetManager::GetAssetByName<SFPlayer>("player");

	auto player_pos = Point2(canvas_w / 2 - player->GetBoundingBox()->GetWidth() / 2, canvas_h - player->GetBoundingBox()->GetHeight());
	player->SetPosition(player_pos);

	SpawnEnemies(10);
	SpawnObstacles(4);

	game_state = SF_PLAY;
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
		case SFEVENT_PAUSE:
			TogglePause();
			break;
		case SFEVENT_UPDATE:
			assets = SFAssetManager::RetrieveAllAssets();
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
		case SFEVENT_MOUSEDOWN:
			mouse_position = event.GetMousePosition();
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
	if(game_state == SF_PLAY) {
		// Update assets before updating state 
		for(auto asset : assets) {
			asset->OnUpdate();
		}

		if(GetNumEnemies() == 0 || !SFAssetManager::GetAssetByName<SFPlayer>("player")->IsAlive()) game_state = SF_END;

		ClearAllDead();
	}
}

void SFApp::OnRender() {

	// 1. Clear visible content
	window->ClearScreen();

	// 2. Test game state
	if(game_state == SF_PLAY) {

		// 3. Render Assets
		for(auto asset : assets) {
			if(!asset->IsOutsideWindow() && asset->IsAlive())
				asset->OnRender();
		}

		// 4. Draw HUD
		DrawHUD();
	} else if (game_state == SF_END) { 
		DrawEndScore(); 
	} else if (game_state == SF_PAUSED) {
		int wi;
		std::string pause_text = "PAUSED - PRESS ESC TO RESUME";
		TTF_SizeText(window->getFont(), pause_text.c_str(), &wi, NULL);
		SF_UILabel::DrawText(pause_text, window->GetWidth() / 2 - wi / 2, window->GetHeight() / 2, text_colour, window);
	}


	// 5. Switch the off-screen buffer to be on-screen
	window->ShowScreen();

	mouse_position = { 0 ,0 };
}

void SFApp::TogglePause() {
	if(game_state == SF_PAUSED) {
		game_state = SF_PLAY;
	} else if(game_state == SF_PLAY) {
		game_state = SF_PAUSED;
	}
}

void SFApp::FireProjectile() {
	shared_ptr<SFProjectile> bullet = make_shared<SFProjectile>("projectile", SFASSET_PROJECTILE, window, BULLET, NORTH);
	bullet->SetDamage(player->GetDamage());

	auto v = player->GetCenter(); 
	auto pos = Point2(v.getX() - bullet->GetBoundingBox()->GetWidth() / 2, v.getY());
	bullet->SetPosition(pos);

	SFAssetManager::AddAsset<SFProjectile>(bullet);
}

void SFApp::DrawHUD() {
	std::string health_text = "HEALTH : " + std::to_string(player->GetHealth());
	std::string enemies_remaining_text = "ENEMIES : " + std::to_string(GetNumEnemies());
	std::string coin_text = "COINS : " + std::to_string(player->GetCoins());

	int wi;
	TTF_SizeText(window->getFont(), health_text.c_str(), &wi, NULL);

	SF_UILabel::DrawText(health_text, window->GetWidth() / 2 - wi / 2, 0, text_colour, window);
	SF_UILabel::DrawText(enemies_remaining_text, 10, 0, text_colour, window);
	SF_UILabel::DrawText(coin_text, 10, 30, text_colour, window);	
}

void SFApp::DrawEndScore() {
	std::string end_text = "FINAL SCORE : " + std::to_string(player->GetCoins() * 2);

	SF_UILabel::DrawText(end_text, window->GetWidth() / 2 - end_text.length(), 0, text_colour, window);

	SF_UIButton exit_button ("Exit Game", 270, 400, 130, 73, window, [this](void){ is_running = false;});
	exit_button.SetBackgroundAlpha(200);
	exit_button.OnClick(mouse_position);
	exit_button.OnRender();
} 

void SFApp::SpawnObstacles(int amount) {
	for(int i = 0; i < amount; i++) {
		auto wall = make_shared<SFObstacle>("wall" + i, SFASSET_OBSTACLE, window);
		auto pos = Point2((window->GetWidth() / amount) * i + wall->GetBoundingBox()->GetWidth() / 2, 300.0f);
		wall->SetPosition(pos);

		SFAssetManager::AddAsset<SFObstacle>(wall);
	}
}

void SFApp::SpawnEnemies(int amount) {
	for (int i = 0; i < amount; i++) {
		// place an alien at width/number_of_aliens * i
		auto alien = make_shared<SFEnemy>("alien" + i, SFASSET_ALIEN, window, ELITE);
		auto pos = Point2((window->GetWidth() / amount) * i + alien->GetBoundingBox()->GetWidth() / 2, 100.0f);
		alien->SetPosition(pos);

		SFAssetManager::AddAsset<SFEnemy>(alien);
	}
}

int SFApp::GetNumEnemies() {
	int num = 0;
	for(auto asset : assets) {
		if(asset->GetType() == SFASSET_ALIEN) num++;
	}

	return num;
}

void SFApp::ClearAllDead() {
	for(auto asset : assets) {
		if(!asset->IsAlive()) SFAssetManager::RemoveAsset(asset);
	}
}
