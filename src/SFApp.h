#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <list>     // Pull in list

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"
#include "SFPlayer.h"
#include "SF_UILabel.h"

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
	
	void ClearDeadCoins();
	void ClearDeadAliens();

    bool is_running;

    shared_ptr<SFWindow> window;

    shared_ptr<SFPlayer> player;
    
    list<shared_ptr<SFAsset> > projectiles;
    list<shared_ptr<SFAsset> > aliens;
    list<shared_ptr<SFAsset> > coins;
};

#endif
