#ifndef SFPARTICLE_H
#define SFPARTICLE_H

#include <SDL.h>
#include <SDL_image.h>

#include "SFMath.h"
#include "SFBoundingBox.h"
#include "SFWindow.h"

#include <cstdlib>
#include <iostream>
#include <memory>

class SFParticle 
{
	public:

		SFParticle(int, int, int, std::shared_ptr<SFWindow>);
		~SFParticle();

		void 							OnUpdate();
		void 							OnRender();

		bool 							IsDead();

	private:

		int 							frame;

		SDL_Texture* 					sprite;
		std::shared_ptr<SFWindow> 		sfwindow;
		std::shared_ptr<SFBoundingBox> 	bbox;

};
#endif
