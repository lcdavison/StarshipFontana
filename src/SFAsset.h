#ifndef SFASSET_H
#define SFASSET_H

#include <string>
#include <memory>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFWindow.h"
#include "SFBoundingBox.h"
#include "SFMath.h"

/**
 * We could create SFPlayer, SFProjectile and SFAsset which are subclasses
 * of SFAsset.  However, I've made an implementation decision to use this
 * enum to mark the type of the SFAsset.  If we add more asset types then
 * the subclassing strategy becomes a better option.
 */
enum SFASSETTYPE { SFASSET_PLAYER, SFASSET_PROJECTILE, SFASSET_ALIEN, SFASSET_COIN };

/*--SFASSET INTERFACE--*/
class ISFAsset {
	public:
		virtual void OnUpdate() = 0;
};

class SFAsset : public ISFAsset {
	public:
		SFAsset(const std::string, const SFASSETTYPE, const std::shared_ptr<SFWindow>);
		SFAsset(const SFAsset&);
		virtual ~SFAsset();

		void OnUpdate();
		std::string GetName() const;
		SFASSETTYPE GetType() const;

		virtual void OnRender();

		virtual void      SetPosition(Point2 &);
		virtual Point2    GetPosition();
		virtual Point2    GetCenter();
		virtual bool	  IsOutsideWindow();	// Test assets position against window boundaries	
		virtual float     DistanceTo(std::shared_ptr<SFAsset>);

		virtual void      GoEast();
		virtual void      GoWest();
		virtual void      GoNorth();
		virtual void      GoSouth();

		virtual void      SetNotAlive();
		virtual bool      IsAlive();
		virtual void      HandleCollision();

		virtual bool                      CollidesWith(shared_ptr<SFAsset>);
		virtual shared_ptr<SFBoundingBox> GetBoundingBox();

		// Movement
		virtual void	  MoveTowards(std::shared_ptr<SFAsset>);
		virtual void	  LinearInterpolate(std::shared_ptr<SFAsset>);

	protected:
		virtual void SetupSprite();

		/*---Movement---*/
		bool is_moving = false;

		float movement_speed = 2.0f;
		float initial_distance;

		std::shared_ptr<Vector2> move_direction;
		std::shared_ptr<Point2> end_point;

		/*---Asset Data---*/
		std::string name;
		bool alive = true;
		int lifetime;

		SDL_Texture               * sprite;
		shared_ptr<SFBoundingBox>   bbox;
		SFASSETTYPE                 type;
		std::shared_ptr<SFWindow>   sf_window;
};

#endif
