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

enum SF_BUTTONSTATE { SFBUTTON_IDLE, SFBUTTON_HOVER, SFBUTTON_CLICK };

class SF_UIButton {
	public:
		SF_UIButton(std::string, int, int, int, int, std::shared_ptr<SFWindow>, std::function<void (void)>);
		~SF_UIButton();

		void OnClick(MousePos); 

		void OnRender();
		void SetAlpha(int);
	private:
		std::function<void (void)> OnClickFunction;	//	Function to run when button is clicked

		std::string text;

		int x, y;
		int width, height;

		SDL_Texture* texture;
		SDL_Rect	 bounds;

		SF_BUTTONSTATE state;
		std::shared_ptr<SFWindow>		sf_window;
};
#endif
