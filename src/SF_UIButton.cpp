#include "SF_UIButton.h" 

SF_UIButton::SF_UIButton(std::string text, int x, int y, int w, int h, std::shared_ptr<SFWindow> window, std::function<void (void)> click_func) : text(text), x(x), y(y), width(w), height(h), sf_window(window) {

	OnClickFunction	= click_func;

	// TODO: Seperate textures so they can have different alpha values
	
	SDL_Color text_color = { 0, 0, 255, 0 };

	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_Surface* text_surface = TTF_RenderText_Blended(sf_window->getFont(), text.c_str(), text_color);

	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
	
	SDL_BlitSurface(text_surface, NULL, surface, NULL);

	if(surface != nullptr) {
		texture = SDL_CreateTextureFromSurface(sf_window->getRenderer(), surface);	
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

		SDL_FreeSurface(surface);
		SDL_FreeSurface(text_surface);
	} else {
		std::cout << "Failed to create surface" << std::endl;
	}

	bounds = { x, y, width, height };
}

SF_UIButton::~SF_UIButton() {
	SDL_DestroyTexture(texture);
} 

void SF_UIButton::OnClick() {
	OnClickFunction();
} 

void SF_UIButton::OnRender() {
	SDL_RenderCopy(sf_window->getRenderer(), texture, NULL, &bounds);
}

void SF_UIButton::SetAlpha(int value) { SDL_SetTextureAlphaMod(texture, value); }
