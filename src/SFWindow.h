#ifndef SFWINDOW_H
#define SFWINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "SFCommon.h"

#define FIRST_SUPPORTED -1

class SFWindow {
	public:
		SFWindow(Uint32 w, Uint32 h, SDL_Color drawColor);
		~SFWindow();

		void ClearScreen();
		void ShowScreen();

		int GetWidth();
		int GetHeight();

		SDL_Window* getWindow();
		SDL_Renderer* getRenderer();
		TTF_Font* getFont();
	private:
		SDL_Window*   window;
		SDL_Renderer* renderer;
		TTF_Font*	  font;
};

#endif
