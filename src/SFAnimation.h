#ifndef SFANIMATION_H
#define SFANIMATION_H

#include <SDL.h>
#include <SDL_image.h>

class SFAnimation {
	public:
		SFAnimation();
		~SFAnimation();
	private:
		int current_frame = 0;
		SDL_Texture* sprite_sheet;
};
#endif
