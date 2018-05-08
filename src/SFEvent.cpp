#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */
SFEvent::SFEvent(const SDL_Event & event) 
{
	switch (event.type) 
	{
		case SDL_QUIT:
			code = SFEVENT_QUIT;
			break;

		case SDL_USEREVENT:
			code = SFEVENT_UPDATE;
			break;

		case SDL_MOUSEBUTTONDOWN:
			code = SFEVENT_MOUSEDOWN;
			mouse_position.x = event.button.x;
			mouse_position.y = event.button.y;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) 
			{
				case SDLK_LEFT:
					code = SFEVENT_PLAYER_LEFT;
					break;

				case SDLK_RIGHT:
					code = SFEVENT_PLAYER_RIGHT;
					break;

				case SDLK_UP:
					code = SFEVENT_PLAYER_UP;
					break;

				case SDLK_DOWN:
					code = SFEVENT_PLAYER_DOWN;
					break;

				case SDLK_SPACE:
					code = SFEVENT_FIRE;
					break;

				case SDLK_q:
					code = SFEVENT_QUIT;
					break;

				case SDLK_ESCAPE:
					code = SFEVENT_PAUSE;
					break;
			}
			break;

		default:
			code = SFEVENT_NULL;
			break;
	}
}

//	
//	GetCode
//		Returns returns the SFEvent code
//
SFEVENT SFEvent::GetCode() 
{
	return code;
}

//	
//	GetMousePosition
//		Returns the mouse position
//
MousePos SFEvent::GetMousePosition() 
{ 
	return mouse_position; 
} 
