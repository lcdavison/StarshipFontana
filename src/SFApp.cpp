#include "SFApp.h"

#include "SF_UIButton.h" // Remove Later

// TODO: Vary the enemy types when starting the level.
// TODO: Add scenes to determine game behaviour
// TODO: Add Query To Retrieve the pixel width of text, to set central text
// TODO: Add an exit button
// 		

SFApp::SFApp(std::shared_ptr<SFWindow> window) : is_running(true), window(window) {
	int canvas_w = window->GetWidth();
	int canvas_h = window->GetHeight();

	SFAssetManager::CreateAsset<SFPlayer>("player", SFASSET_PLAYER, window);
	player = SFAssetManager::FindAssetByName<SFPlayer>("player");

	auto player_pos = Point2(canvas_w / 2 - player->GetBoundingBox()->GetWidth() / 2, canvas_h - player->GetBoundingBox()->GetHeight());
	player->SetPosition(player_pos);

	SpawnEnemies(10);

	game_state = SF_PLAY;

	SF_UIButton button ("test", 0,0,0,0, [](void){ std::cout << "Hello World" << std::endl ;});
	button.OnClick();
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
			MousePos position = event.GetMousePosition();
			std::cout << "X : " << position.x << " Y : " << position.y << std::endl;
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

	if(GetNumEnemies() == 0) game_state = SF_END;

	if(game_state != SF_END) {

		for(auto asset : assets) {
			asset->OnUpdate();
		}

		ClearAllDead();
	}
}

void SFApp::OnRender() {

	// 1. Clear visible content
	window->ClearScreen();

	if(game_state != SF_END) {

		// 2. Render Assets
		for(auto asset : assets) {
			if(!asset->IsOutsideWindow() && asset->IsAlive())
				asset->OnRender();
		}

		// 3. Draw HUD
		DrawHUD();
	} else { DrawEndScore(); }

	// 4. Switch the off-screen buffer to be on-screen
	window->ShowScreen();
}

void SFApp::FireProjectile() {

	shared_ptr<SFProjectile> bullet = make_shared<SFProjectile>("projectile", SFASSET_PROJECTILE, window, BULLET);
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

	SF_UILabel::DrawText(health_text, window->GetWidth() / 2 - health_text.length(), 0, text_colour, window);
	SF_UILabel::DrawText(enemies_remaining_text, 10, 0, text_colour, window);
	SF_UILabel::DrawText(coin_text, 10, 30, text_colour, window);	
}

void SFApp::DrawEndScore() {
	std::string end_text = "FINAL SCORE : " + std::to_string(player->GetCoins() * 2);

	SF_UILabel::DrawText(end_text, window->GetWidth() / 2, 0, text_colour, window);
} 

void SFApp::SpawnEnemies(int amount) {
	for (int i = 0; i < amount; i++) {
		// place an alien at width/number_of_aliens * i
		auto alien = make_shared<SFEnemy>("alien" + i, SFASSET_ALIEN, window, ELITE);
		auto pos = Point2((window->GetWidth() / amount) * i + alien->GetBoundingBox()->GetWidth() / 2, 200.0f);
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
		assert(asset != NULL);
		if(!asset->IsAlive()) SFAssetManager::RemoveAsset(asset);
	}
}
