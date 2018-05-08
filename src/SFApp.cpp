#include "SFApp.h"

// TODO: Code Cleanup - Make it more readable
// TODO: Change the README.md 

SFApp::SFApp(std::shared_ptr<SFWindow> window) : is_running(true), window(window) {

	CreateButtons();
	CreateLabels();

	game_state = SF_MENU;
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
			if(game_state == SF_PLAY || game_state == SF_PAUSED) TogglePause();
			break;
		case SFEVENT_UPDATE:
			assets = SFAssetManager::RetrieveAllAssets();
			OnUpdate();
			OnRender();
			break;
		case SFEVENT_PLAYER_LEFT:
			if(game_state == SF_PLAY) player->GoWest();
			break;
		case SFEVENT_PLAYER_RIGHT:
			if(game_state == SF_PLAY) player->GoEast();
			break;
		case SFEVENT_PLAYER_UP:
			if(game_state == SF_PLAY) player->GoNorth();
			break;
		case SFEVENT_PLAYER_DOWN:
			if(game_state == SF_PLAY) player->GoSouth();
			break;
		case SFEVENT_FIRE:	
			if(game_state == SF_PLAY) FireProjectile();
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
	switch(game_state) {
		case SF_MENU:
			DrawMainMenu();
			break;
		case SF_END:
			DrawEndScore();
			break;
		case SF_PAUSED:
			DrawPauseMenu();
			break;
	}

	if(game_state == SF_PLAY) {

		// 3. Render Assets
		for(auto asset : assets) {
			if(!asset->IsOutsideWindow() && asset->IsAlive())
				asset->OnRender();
		}

		// 4. Draw HUD
		DrawHUD();	
	}

	// 5. Switch the off-screen buffer to be on-screen
	window->ShowScreen();

	// 6. Reset mouse position
	mouse_position = { 0 ,0 };
}

void SFApp::StartGame() {
	SFAssetManager::Clear();

	SpawnPlayer();
	SpawnObstacles(4);
	SpawnEnemies(15);

	game_state = SF_PLAY;
}

void SFApp::TogglePause() {
	game_state = (game_state == SF_PAUSED) ? SF_PLAY : SF_PAUSED;	
}

void SFApp::FireProjectile() {
	shared_ptr<SFProjectile> bullet = make_shared<SFProjectile>("projectile", SFASSET_PROJECTILE, window, BULLET, NORTH);
	bullet->SetDamage(player->GetDamage());

	auto v = player->GetCenter(); 
	auto pos = Point2(v.getX() - bullet->GetBoundingBox()->GetWidth() / 2, v.getY() - bullet->GetBoundingBox()->GetWidth() * 2);
	bullet->SetPosition(pos);

	SFAssetManager::AddAsset<SFProjectile>(bullet);
}

void SFApp::CreateButtons() {
	play_button = std::make_shared<SF_UIButton>("Play Game", window->GetWidth() / 2 - 65, window->GetHeight() / 2, 130, 73, window, [this](void){ StartGame(); });
	play_button->SetBackgroundAlpha(200);

	exit_button = std::make_shared<SF_UIButton>("Exit Game", window->GetWidth() / 2 - 65, window->GetHeight() / 2 + 100, 130, 73, window, [this](void){ is_running = false; });
	exit_button->SetBackgroundAlpha(200);
	
		restart_button = std::make_shared<SF_UIButton>("Play Again", window->GetWidth() / 2 - 65, window->GetHeight() / 2, 130, 73, window, [this](void){ StartGame(); });
	restart_button->SetBackgroundAlpha(200);

	resume_button = std::make_shared<SF_UIButton>("Resume Game", window->GetWidth() / 2 - 65, window->GetHeight() / 2, 150, 84, window, [this](void){ game_state = SF_PLAY; });
	resume_button->SetBackgroundAlpha(200);

	menu_button = std::make_shared<SF_UIButton>("Return To Main", window->GetWidth() / 2 - 65, window->GetHeight() / 2 + 100, 150, 84, window, [this](void){ game_state = SF_MENU; SFAssetManager::Clear(); });
	menu_button->SetBackgroundAlpha(200);
}

void SFApp::CreateLabels() {
	int text_width;
	TTF_SizeText(window->getFont(), "STARSHIP FONTANA", &text_width, NULL);
	title = std::make_shared<SF_UILabel>("STARSHIP FONTANA", window->GetWidth() / 2 - text_width / 2, 0, text_colour, window, SF_FONT_NORMAL);

	TTF_SizeText(window->getSmallFont(), "by Luke Davison", &text_width, NULL);
	author = std::make_shared<SF_UILabel>("by Luke Davison", window->GetWidth() / 2 - text_width / 2, 20, text_colour, window, SF_FONT_SMALL);
	
	TTF_SizeText(window->getFont(), "PAUSED", &text_width, NULL);
	pause = std::make_shared<SF_UILabel>("PAUSED", window->GetWidth() / 2 - text_width / 2, window->GetHeight() / 2 - 100, text_colour, window, SF_FONT_NORMAL);

}

void SFApp::DrawMainMenu() {
	title->OnRender();
	author->OnRender();

	play_button->OnClick(mouse_position);
	play_button->OnRender();

	exit_button->OnClick(mouse_position);
	exit_button->OnRender();
}

void SFApp::DrawPauseMenu() {
	pause->OnRender();

	resume_button->OnClick(mouse_position);
	resume_button->OnRender();

	menu_button->OnClick(mouse_position);
	menu_button->OnRender();
}

void SFApp::DrawHUD() {
	std::string health_text = "HEALTH : " + std::to_string(player->GetHealth());
	std::string enemies_remaining_text = "ENEMIES : " + std::to_string(GetNumEnemies());
	std::string coin_text = "COINS : " + std::to_string(player->GetCoins());

	int wi;
	TTF_SizeText(window->getFont(), health_text.c_str(), &wi, NULL);

	SF_UILabel::DrawText(health_text, window->GetWidth() / 2 - wi / 2, 0, text_colour, window, SF_FONT_NORMAL);
	SF_UILabel::DrawText(enemies_remaining_text, 10, 0, text_colour, window, SF_FONT_NORMAL);
	SF_UILabel::DrawText(coin_text, 10, 30, text_colour, window, SF_FONT_NORMAL);	
}

void SFApp::DrawEndScore() {
	std::string end_text = "FINAL SCORE : " + std::to_string(player->GetCoins() * 2);

	int wi;
	TTF_SizeText(window->getFont(), end_text.c_str(), &wi, NULL);
	SF_UILabel::DrawText(end_text, window->GetWidth() / 2 - wi / 2, 0, text_colour, window, SF_FONT_NORMAL);

	restart_button->OnClick(mouse_position);
	restart_button->OnRender();

	exit_button->OnClick(mouse_position);
	exit_button->OnRender();
} 

void SFApp::SpawnPlayer() {
	SFAssetManager::CreateAsset<SFPlayer>("player", SFASSET_PLAYER, window);
	player = SFAssetManager::GetAssetByName<SFPlayer>("player");

	auto player_pos = Point2(window->GetWidth() / 2 - player->GetBoundingBox()->GetWidth() / 2, window->GetHeight() - player->GetBoundingBox()->GetHeight());
	player->SetPosition(player_pos);
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
		// Place an alien at width/number_of_aliens * i
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
