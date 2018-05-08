#include "SFWindow.h"

SFWindow::SFWindow(Uint32 w, Uint32 h, SDL_Color drawColor) {
    
    window = SDL_CreateWindow(
        "Starship Fontana",
        SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_SHOWN
    );

    if (!window) 
        throw SFException("Failed to create window");
    
    renderer = SDL_CreateRenderer(
			window, 
			FIRST_SUPPORTED, 
			SDL_RENDERER_ACCELERATED
	);

    if (!renderer) 
        throw SFException("Failed to create renderer");
    

    SDL_SetRenderDrawColor(
			renderer, 
			drawColor.r, 
			drawColor.g, 
			drawColor.b, 
			drawColor.a
	);

	font = TTF_OpenFont("assets/fonts/arial.ttf", 20);
	if(!font)
		throw SFException("Failed to load font");

	small_font = TTF_OpenFont("assets/fonts/arial.ttf", 14);
	if(!small_font)
		throw SFException("Failed to load font");
}

SFWindow::~SFWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	if(font) TTF_CloseFont(font);
	if(small_font) TTF_CloseFont(small_font);
}

void SFWindow::ClearScreen() {
    SDL_RenderClear(renderer);
}

void SFWindow::ShowScreen() {
    SDL_RenderPresent(renderer);
}

int SFWindow::GetWidth() {
    int w;
    SDL_GetRendererOutputSize(renderer, &w, NULL);
    return w;
}

int SFWindow::GetHeight() {
    int h;
    SDL_GetRendererOutputSize(renderer, NULL, &h);
    return h;
}

SDL_Window* SFWindow::getWindow() {
    return window;
}

SDL_Renderer* SFWindow::getRenderer() {
    return renderer;
}

TTF_Font* SFWindow::getFont() {
	return font;
}

TTF_Font* SFWindow::getSmallFont() {
	return small_font;
}
