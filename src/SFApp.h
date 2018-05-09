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
class SFApp 
{
	public:

		SFApp(std::shared_ptr<SFWindow>);

		void 									OnEvent(SFEvent &);
		void 									StartMainLoop();
		void 									OnUpdate();
		void 									OnRender();

	private:

		/*---STATE---*/
		enum SFGAMESTATE { SF_MENU,
		   				   SF_PLAY, 
						   SF_PAUSED, 
						   SF_END };

		SFGAMESTATE 							game_state;

		void 									StartGame();
		void 									TogglePause();

		bool 									is_running;

		/*---UI---*/
		SDL_Color 								text_colour = { 0, 255, 0, 255 };

		void 									CreateButtons();
		void 									CreateLabels();

		void 									DrawMainMenu();
		void 									DrawPauseMenu();
		void 									DrawHUD();
		void 									DrawEndScore();

		std::shared_ptr<SF_UILabel> 			pause;

		std::list<std::shared_ptr<SF_UIButton>>	menu_buttons;
		std::list<std::shared_ptr<SF_UIButton>> pause_buttons;
		std::list<std::shared_ptr<SF_UIButton>> end_buttons;

		std::list<std::shared_ptr<SF_UILabel>>	menu_labels;

		/*---SPAWNING---*/
		void 									SpawnPlayer();
		void 									SpawnObstacles(int);
		void 									SpawnEnemies(int);
		void 									FireProjectile();

		int  									GetNumEnemies();
		
		/*---CLEARING---*/
		void						 			ClearAllDead();

		/*---INPUT---*/
		MousePos 								mouse_position;
		
		/*---POINTERS---*/
		shared_ptr<SFWindow> 					window;
		shared_ptr<SFPlayer> 					player;

		/*---ASSETS---*/
		vector<std::shared_ptr<SFAsset>> 		assets;

};
#endif
