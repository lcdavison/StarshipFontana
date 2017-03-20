#include <SDL.h> // Pull in the SDL definitions
#include <memory>     // Pull in std::shared_ptr

using namespace std;  // So that we can write `vector` rather than `std::vector`

#include "SFCommon.h"
#include "SFApp.h"

#define FIRST_SUPPORTED -1
#define SECOND_MILLIS 1000
#define FRAME_RATE 60

enum UserEvents { UPDATE_EVENT };

Uint32 PushUpdateEvent(Uint32 interval, void *param) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = UPDATE_EVENT;
    event.user.data1 = 0;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
    return interval;
}

shared_ptr<SFWindow> InitGraphics() {
    Uint32 width = 640;
    Uint32 height = 480;
    SDL_Color drawColor = { 128, 128, 128, SDL_ALPHA_OPAQUE };

    // Initialise SDL - when using C/C++ it's common to have to
    // initialise libraries by calling a function within them.
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        cerr << "Failed to initialise SDL: " << SDL_GetError() << endl;
        throw SF_ERROR_INIT;
    }

    // Create a new window
    SDL_Window * window = SDL_CreateWindow(
        "StarShip Fontana",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_SHOWN
    );

    if (!window) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        throw SF_ERROR_VIDEOMODE;
    }
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, FIRST_SUPPORTED, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        throw SF_ERROR_VIDEOMODE;
    }

    SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);

    return make_shared<SFWindow>(window, renderer);
}

int main(int arc, char ** argv) {
    shared_ptr<SFWindow> window = nullptr;

    // Initialise graphics context
    try {
        window = InitGraphics();
    }
    catch (SFError e) {
        return e;
    }

    // Initialise world
    shared_ptr<SFApp> sfapp = make_shared<SFApp>(window);

    // Set up top-level timer to UpdateWorld
    // Call the function "display" every delay milliseconds
    int delay = SECOND_MILLIS / FRAME_RATE;
    SDL_AddTimer(delay, PushUpdateEvent, NULL);

    // Start game loop
    sfapp->OnExecute();

    // Delete the app -- allows the SFApp object to do its own cleanup
    sfapp.reset();
    return SF_ERROR_NONE;
}