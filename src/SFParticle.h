#ifndef SFPARTICLE_H
#define SFPARTICLE_H

#include <SDL.h>
#include <SDL_image.h>

#include <memory>

class SFParticle 
{
	public:
		SFParticle();

		void Render();

		bool IsDead();
	private:
		int frame;

		std::shared_ptr<SFBoundingBox> bbox;
		SDL_Texture* sprite;
};
#endif
