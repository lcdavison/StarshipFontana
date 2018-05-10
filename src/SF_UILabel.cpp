#include "SF_UILabel.h"

SF_UILabel::SF_UILabel(const std::string& text,
		       const short& x, const short& y,
		       SDL_Color colour,
		       std::shared_ptr<SFWindow> window,
		       SFFONTSIZE size)
  		       : window(window) 
{
	switch(size) 
	{
		case SF_FONT_NORMAL:
			texture = CreateTextureFromString(text, window->getFont(), colour, window);
			break;
		case SF_FONT_SMALL:
			texture = CreateTextureFromString(text, window->getSmallFont(), colour, window);
			break;
	}

	int width, height;
	SDL_QueryTexture(texture,
			 0, 0,
			 &width, &height);

	destination = { x, y, width, height };
}

SF_UILabel::~SF_UILabel() 
{
	if(texture) 
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

/*
	OnRender
 		Renders the label
*/ 
void SF_UILabel::OnRender() 
{
	SDL_RenderCopy(window->getRenderer(), texture, NULL, &destination);
}

/*
	DrawText
		Easily draw dynamic text to the screen
*/
void SF_UILabel::DrawText(const std::string& text,
			  const short& x, const short& y,
			  SDL_Color colour,
			  std::shared_ptr<SFWindow> window,
			  SFFONTSIZE size) 
{
	SDL_Texture* texture;

	switch(size)
	{
		case SF_FONT_NORMAL:
			texture = CreateTextureFromString(text, window->getFont(), colour, window);
			break;
			
		case SF_FONT_SMALL:
			texture = CreateTextureFromString(text, window->getSmallFont(), colour, window);
			break;
	}

	int width, height;
	SDL_QueryTexture(texture, 0, 0, &width, &height);

	SDL_Rect dst = { x, y, width, height };

	SDL_RenderCopy(window->getRenderer(), texture, NULL, &dst);

	SDL_DestroyTexture(texture);
}

/*
	CreateTextureFromString
		Creates an SDL_Texture using a string and TTF_Font
*/
SDL_Texture* SF_UILabel::CreateTextureFromString(const std::string& text,
						 TTF_Font* font,
						 SDL_Color colour,
						 std::shared_ptr<SFWindow> window) 
{
	SDL_Texture* TextTexture = nullptr;
	SDL_Surface* TextSurface = TTF_RenderText_Blended(font, text.c_str(), colour);

	if (TextSurface != nullptr) 
	{
		TextTexture = SDL_CreateTextureFromSurface(window->getRenderer(), TextSurface);
		SDL_FreeSurface(TextSurface);

	} 
	else 
	{
		std::cout << "Failed To Create Texture From String : " << text << std::endl;
		std::cout << TTF_GetError() << std::endl;
	}

	return TextTexture;
}
