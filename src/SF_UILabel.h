#ifndef SF_UILABEL_H
#define SF_UILABEL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <iostream>

#include "SFWindow.h"

enum SFFONTSIZE { SF_FONT_NORMAL, SF_FONT_SMALL }; 

class SF_UILabel {

public:
	SF_UILabel(const std::string&, const short&, const short&, SDL_Color, std::shared_ptr<SFWindow>, SFFONTSIZE);
	~SF_UILabel();

	void OnRender();

	static void DrawText(const std::string&, const short&, const short&, SDL_Color, std::shared_ptr<SFWindow>, SFFONTSIZE);
private:
	static SDL_Texture* CreateTextureFromString(const std::string&, TTF_Font*, SDL_Color, std::shared_ptr<SFWindow>);

	SDL_Rect destination;
	SDL_Texture* texture;
	std::shared_ptr<SFWindow> window;
};
#endif
