#ifndef SFWINDOW_H
#define SFWINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "SFCommon.h"

#define FIRST_SUPPORTED -1

class SFWindow {
	public:
		SFWindow(Uint32, Uint32, SDL_Color);
		~SFWindow();

		void ClearScreen();
		void ShowScreen();

		int GetWidth();
		int GetHeight();

		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();
		TTF_Font* getFont();
		TTF_Font* getSmallFont();
	private:
		SDL_Window*   window;
		SDL_Renderer* renderer;
		TTF_Font*	  font;
		TTF_Font*	  small_font;
};

#endif
