#include "SFAnimation.h"

SFAnimation::SFAnimation(const std::string path, const int no_of_sprites) {
	frames = no_of_sprites;


	
}

SFAnimation::~SFAnimation() {
	SDL_DestroyTexture(sprite_sheet);
}
