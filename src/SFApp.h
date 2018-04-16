#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <list>     // Pull in list
#include <vector>   // Pull in vector

#include <assert.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"
#include "SFPlayer.h"
#include "SFEnemy.h"
#include "SFCoin.h"
#include "SFProjectile.h"
#include "SF_UILabel.h"
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

		void FireProjectile();
	private:
		void DrawHUD();

		void SpawnEnemies(int);

		void ClearAllDead();

		bool is_running;
		int enemies_remaining;

		shared_ptr<SFWindow> window;
		shared_ptr<SFPlayer> player;

		vector<std::shared_ptr<SFAsset>> assets;
};

#endif
