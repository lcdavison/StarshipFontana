#ifndef SF_UIBUTTON_H
#define SF_UIBUTTON_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <memory>
#include <functional>
#include <iostream>

#include "SFMath.h"
#include "SFWindow.h"
#include "SFEvent.h"

class SF_UIButton 
{
	public:
		SF_UIButton(std::string, int, int, int, int, std::shared_ptr<SFWindow>, std::function<void (void)>);
		~SF_UIButton();

		void OnClick(MousePos); 

		void OnRender();

		void SetTextAlpha(int);
		void SetBackgroundAlpha(int);
	private:
		std::function<void (void)> OnClickFunction;	//	Function run on button click 

		void CreateBackground();
		void CreateText();

		std::string text;

		int x, y;
		int width, height;
		int text_alpha, background_alpha;

		SDL_Texture* text_texture;
		SDL_Texture* background_texture;

		SDL_Rect	 background_bounds;
		SDL_Rect	 text_bounds;

		std::shared_ptr<SFWindow>		sf_window;
};
#endif
