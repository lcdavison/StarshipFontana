#include "SF_UILabel.h"

void SF_UILabel::DrawText(const std::string& text, const short& x, const short& y, SDL_Color colour, std::shared_ptr<SFWindow> window) {

	SDL_Texture* texture = CreateTextureFromString(text, window->getFont(), colour, window);

	int width, height;

	SDL_QueryTexture(texture, 0, 0, &width, &height);

	SDL_Rect dst = { x, y, width, height };

	SDL_RenderCopy(window->getRenderer(), texture, NULL, &dst);

	SDL_DestroyTexture(texture);
}

SDL_Texture* SF_UILabel::CreateTextureFromString(const std::string& text, TTF_Font* font, SDL_Color colour, std::shared_ptr<SFWindow> window) {
	
	SDL_Texture* TextTexture = nullptr;
	SDL_Surface* TextSurface = TTF_RenderText_Blended(font, text.c_str(), colour);

	if (TextSurface != nullptr) {
	
		TextTexture = SDL_CreateTextureFromSurface(window->getRenderer(), TextSurface);
		SDL_FreeSurface(TextSurface);

	} else {
		
		std::cout << "Failed To Create Texture From String : " << text << std::endl;
		std::cout << TTF_GetError() << std::endl;
	}

	return TextTexture;
}
