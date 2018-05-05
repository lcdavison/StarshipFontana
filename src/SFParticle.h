#ifndef SFPARTICLE_H
#define SFPARTICLE_H

#include <SDL.h>
#include <SDL_image.h>

#include "SFBoundingBox.h"
#include "SFWindow.h"

#include <cstdlib>
#include <iostream>
#include <memory>

class SFParticle 
{
	public:
		SFParticle(int, int, std::shared_ptr<SFWindow>);

		void Render();

		bool IsDead();
	private:
		int frame;

		std::shared_ptr<SFWindow> sfwindow;
		std::shared_ptr<SFBoundingBox> bbox;
		SDL_Texture* sprite;
};
#endif
