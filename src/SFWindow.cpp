#include "SFWindow.h"

SFWindow::SFWindow(Uint32 width, Uint32 height, 
				   SDL_Color draw_colour) 
{
	// Create SDL Window
    window = SDL_CreateWindow(
        "Starship Fontana",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
	
	// Check Window
    if (!window) 
        throw SFException("Failed to create window");
    
	// Create SDL Renderer
    renderer = SDL_CreateRenderer(
			window, 
			FIRST_SUPPORTED, 
			SDL_RENDERER_ACCELERATED
	);

	// Check Renderer
    if (!renderer) 
        throw SFException("Failed to create renderer");
    
	// Set Draw Colour
    SDL_SetRenderDrawColor(
			renderer, 
			draw_colour.r, 
			draw_colour.g, 
			draw_colour.b, 
			draw_colour.a
	);
	
	font = TTF_OpenFont("assets/fonts/arial.ttf", 20);
	if(!font)
		throw SFException("Failed to load font");

	small_font = TTF_OpenFont("assets/fonts/arial.ttf", 14);
	if(!small_font)
		throw SFException("Failed to load font");
}

SFWindow::~SFWindow() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	if(font) TTF_CloseFont(font);
	if(small_font) TTF_CloseFont(small_font);
}

/*
	ClearScreen	
		Clears the renderered images
*/
void SFWindow::ClearScreen() 
{
    SDL_RenderClear(renderer);
}

/*
	ShowScreen
		Shows the buffered image
*/
void SFWindow::ShowScreen() 
{
    SDL_RenderPresent(renderer);
}

/*
	GetWidth
		Returns renderer width
*/
int SFWindow::GetWidth() 
{
    int w;
    SDL_GetRendererOutputSize(renderer, &w, NULL);
    return w;
}

/*
	GetHeight
		Returns renderer height
*/
int SFWindow::GetHeight() 
{
    int h;
    SDL_GetRendererOutputSize(renderer, NULL, &h);
    return h;
}

/*
	getWindow
		Returns SDL_Window handle
*/
SDL_Window* SFWindow::getWindow() 
{
    return window;
}

/*
	getRenderer
		Returns SDL_Renderer handle
*/
SDL_Renderer* SFWindow::getRenderer() 
{
    return renderer;
}

/*
	getFont
		Returns font size 20
*/
TTF_Font* SFWindow::getFont() 
{
	return font;
}

/*
	getSmallFont
		Returns font size 14
*/
TTF_Font* SFWindow::getSmallFont() 
{
	return small_font;
}
