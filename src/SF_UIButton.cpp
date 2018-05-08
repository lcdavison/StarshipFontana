#include "SF_UIButton.h" 

SF_UIButton::SF_UIButton(std::string text, 
						 int x, int y, 
						 int w, int h, 
						 std::shared_ptr<SFWindow> window, 
						 std::function<void (void)> click_func) 
						 : text(text), 
						 x(x), y(y), 
						 width(w), height(h), 
						 sf_window(window) 
{
	OnClickFunction	= click_func;

	CreateBackground();
	CreateText();
}

SF_UIButton::~SF_UIButton() 
{
	if(text_texture) 
	{
		SDL_DestroyTexture(text_texture);
		text_texture = nullptr;
	}

	if(background_texture) 
	{
		SDL_DestroyTexture(background_texture);
		background_texture = nullptr;
	}
} 

//	
//	CreateBackground
//	Creates the background for the button
//
void SF_UIButton::CreateBackground() 
{
	SDL_Surface* background_surface = SDL_CreateRGBSurface(0, width, height, 
														   32, 0, 0, 0, 0);

	SDL_FillRect(background_surface, NULL, SDL_MapRGB(background_surface->format, 255, 0, 0));

	if(background_surface != nullptr) 
	{
		background_texture = SDL_CreateTextureFromSurface(sf_window->getRenderer(), background_surface);	

		SDL_SetTextureBlendMode(background_texture, SDL_BLENDMODE_BLEND);

		SDL_FreeSurface(background_surface);
	} 
	else 
	{
		std::cout << "Failed to create background surface" << std::endl;
	}

	background_bounds = { x, y, width, height };
}

//
//	CreateText
//	Creates the text for the button
//
void SF_UIButton::CreateText() 
{
	SDL_Color text_color = { 0, 0, 100, 0 };

	SDL_Surface* text_surface = TTF_RenderText_Blended(sf_window->getFont(), 
													   text.c_str(), 
													   text_color);
	int wi, he;

	if(text_surface != nullptr) 
	{
		// Create Texture
		text_texture = SDL_CreateTextureFromSurface(sf_window->getRenderer(), text_surface);

		// Retrieve Text Dimensions
		TTF_SizeText(sf_window->getFont(), 
					 text.c_str(), 
				 	 &wi, &he);

		// Destroy Surface
		SDL_FreeSurface(text_surface);
	} 
	else 
	{
		std::cout << "Failed to create text surface" << std::endl;
	}

	// Position text relative to button
	text_bounds = { x + width / 2 - wi / 2, 
				    y + height / 2 - he / 2, 
					wi, he };
}

// 
//	OnClick
//	Runs OnClick function
void SF_UIButton::OnClick(MousePos position) 
{
	if(position.x > x && position.x < x + width 
	   && position.y > y && position.y < y + height)	
	   OnClickFunction();
} 

//	
//	OnRender
//	Renders the button background and text
//
void SF_UIButton::OnRender() 
{
	SDL_RenderCopy(sf_window->getRenderer(), 
				   background_texture, 
				   NULL, 
				   &background_bounds);

	SDL_RenderCopy(sf_window->getRenderer(), 
				   text_texture, 
				   NULL, 
				   &text_bounds);
}

//
//	SetTextAlpha
//	Sets alpha value for button text
//
void SF_UIButton::SetTextAlpha(int value) 
{ 
	SDL_SetTextureAlphaMod(text_texture, value); 
}

//
//	SetBackgroundAlpha
//	Sets alpha value for button background
//
void SF_UIButton::SetBackgroundAlpha(int value) 
{ 
	SDL_SetTextureAlphaMod(background_texture, value); 
}
