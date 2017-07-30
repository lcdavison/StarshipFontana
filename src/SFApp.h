#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <list>     // Pull in list

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

/**
 * Represents the StarshipFontana application.  It has responsibilities for:
 * 1. Process game events
 * 2. Update game world
 * 3. Render game world
 */
class SFApp {
public:
    SFApp(std::shared_ptr<SFWindow>);
    virtual ~SFApp();
    void    OnEvent(SFEvent &);
    int     OnExecute();
    void    OnUpdateWorld();
    void    OnRender();

    void    FireProjectile();
private:
    bool                    is_running;

    shared_ptr<SFWindow>       sf_window;

    shared_ptr<SFAsset>        player;
    shared_ptr<SFBoundingBox>  app_box;
    list<shared_ptr<SFAsset> > projectiles;
    list<shared_ptr<SFAsset> > aliens;
    list<shared_ptr<SFAsset> > coins;
};

#endif
