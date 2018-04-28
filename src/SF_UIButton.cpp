#include "SF_UIButton.h" 

SF_UIButton::SF_UIButton(std::string text, int x, int y, int w, int h, std::shared_ptr<SFWindow> window, std::function<void (void)> click_func) : text(text), x(x), y(y), width(w), height(h), sf_window(window) {

	OnClickFunction	= click_func;
	
	SDL_Color text_color = { 0, 0, 255, 0 };

	SDL_Surface* background_surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

	SDL_FillRect(background_surface, NULL, SDL_MapRGB(background_surface->format, 255, 0, 0));
	
	if(background_surface != nullptr) {
		background_texture = SDL_CreateTextureFromSurface(sf_window->getRenderer(), background_surface);	

		SDL_SetTextureBlendMode(background_texture, SDL_BLENDMODE_BLEND);

		SDL_FreeSurface(background_surface);
	} else {
		std::cout << "Failed to create background surface" << std::endl;
	}

	SDL_Surface* text_surface = TTF_RenderText_Blended(sf_window->getFont(), text.c_str(), text_color);

	if(text_surface != nullptr) {
		text_texture = SDL_CreateTextureFromSurface(sf_window->getRenderer(), text_surface);

		SDL_SetTextureBlendMode(text_texture, SDL_BLENDMODE_BLEND);

		SDL_FreeSurface(text_surface);
	} else {
		std::cout << "Failed to create text surface" << std::endl;
	}

	background_bounds = { x, y, width, height };
	text_bounds = { x + width / 4, y + height / 4, width / 2, height / 2 };	// Relative to button
}

SF_UIButton::~SF_UIButton() {
	SDL_DestroyTexture(text_texture);
	SDL_DestroyTexture(background_texture);
} 

void SF_UIButton::OnClick(MousePos position) {
	if(position.x > x && position.x < x + width && position.y > y && position.y < y + height) OnClickFunction();
} 

void SF_UIButton::OnRender() {
	SDL_RenderCopy(sf_window->getRenderer(), background_texture, NULL, &background_bounds);
	SDL_RenderCopy(sf_window->getRenderer(), text_texture, NULL, &text_bounds);
}

void SF_UIButton::SetTextAlpha(int value) { SDL_SetTextureAlphaMod(text_texture, value); }

void SF_UIButton::SetBackgroundAlpha(int value) { SDL_SetTextureAlphaMod(background_texture, value); }
