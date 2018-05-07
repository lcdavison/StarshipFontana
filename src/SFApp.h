#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <list>     // Pull in list
#include <vector>   // Pull in vector

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SF_UILabel.h"
#include "SF_UIButton.h"
#include "SFAssetManager.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for:
 * 1. Process game events
 * 2. Update game world
 * 3. Render game world
 */
class SFApp {
	public:
		SFApp(std::shared_ptr<SFWindow>);
		~SFApp();

		void OnEvent(SFEvent &);
		void StartMainLoop();
		void OnUpdate();
		void OnRender();

	private:
		/*---STATE---*/
		enum SFGAMESTATE { SF_MENU, SF_PLAY, SF_PAUSED, SF_END };
		SFGAMESTATE game_state;

		void RestartGame();
		void TogglePause();

		/*---UI---*/
		SDL_Color text_colour = { 0, 255, 0, 255 };

		void DrawMainMenu();
		void DrawPauseMenu();
		void DrawHUD();
		void DrawEndScore();

		/*---SPAWNING---*/
		void SpawnPlayer();
		void SpawnObstacles(int);
		void SpawnEnemies(int);
		void FireProjectile();

		int  GetNumEnemies();
		
		/*---CLEARING---*/
		void ClearAllDead();

		bool is_running;

		MousePos mouse_position;

		shared_ptr<SFWindow> window;
		shared_ptr<SFPlayer> player;

		vector<std::shared_ptr<SFAsset>> assets;
};
#endif
