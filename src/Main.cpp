#include <SDL.h>
#include <memory>

using namespace std;

#include "SFCommon.h"
#include "SFApp.h"

#define SECOND_MILLIS 1000
#define FRAME_RATE 60

enum UserEvents { UPDATE_EVENT };

//
//	PushUpdateEvent
//		Pushes a new update event to the SDL Event Queue
//
Uint32 PushUpdateEvent(Uint32 interval, void *param) 
{
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = UPDATE_EVENT;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

//
//	InitGraphics
//		Initializes the libraries 
//		Creates a window
//
shared_ptr<SFWindow> InitGraphics() 
{
	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO 
				 | SDL_INIT_AUDIO 
				 | SDL_INIT_TIMER) < 0) 
	{
		throw SFException("Failed to initialise SDL");
	}

	// Initialize TTF
	if (TTF_Init() < 0) 
		throw SFException("Failed to initialise TTF");
	
	// Initialize IMG
	if(IMG_Init(IMG_INIT_PNG) < 0)
	   throw SFException("Failed to initialize IMG ");

	// Window width & height
	Uint32 width = 640;
	Uint32 height = 480;

	// Background color 
	SDL_Color draw_colour = { 0, 100, 255, SDL_ALPHA_OPAQUE };

	return make_shared<SFWindow>(width, height, draw_colour);
}

int main(int argc, char ** argv) 
{
	try 
	{
		// Initialise graphics context
		shared_ptr<SFWindow> window = InitGraphics();

		// Initialise world
		shared_ptr<SFApp> game = make_shared<SFApp>(window);

		// Delay in milliseconds
		int delay = SECOND_MILLIS / FRAME_RATE;	

		// Set up the timer to call "PushUpdateEvent" every delay milliseconds
		SDL_AddTimer(delay, PushUpdateEvent, NULL);

		// Start game loop
		game->StartMainLoop();

	} 
	catch (SFException& e) 
	{
		cout << "Exception occurred!" << endl;
		cout << e.what() << endl;
		cout << "Exception details: " << SDL_GetError() << endl;
	}

	// Close IMG library
	IMG_Quit();

	// Close TTF library
	TTF_Quit();

	// Close SDL library
	SDL_Quit();

	return 0;
}
