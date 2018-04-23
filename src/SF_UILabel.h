#ifndef SF_UILABEL_H
#define SF_UILABEL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <iostream>

#include "SFWindow.h"

class SF_UILabel {

public:
	static void DrawText(const std::string&, const short&, const short&, SDL_Color, std::shared_ptr<SFWindow>);
private:
	static SDL_Texture* CreateTextureFromString(const std::string&, TTF_Font*, SDL_Color, std::shared_ptr<SFWindow>);
};
#endif
