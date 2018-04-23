#ifndef SFANIMATION_H
#define SFANIMATION_H

#include <SDL.h>
#include <SDL_image.h>

#include "SFCommon.h"

class SFAnimation {
	public:
		SFAnimation(const std::string, const int);
		~SFAnimation();

		void NextFrame();
	private:
		int current_frame = 0;
		int frames;
		SDL_Texture* sprite_sheet;
};
#endif
