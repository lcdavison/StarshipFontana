#include "SFWindow.h"

SFWindow::SFWindow(Uint32 w, Uint32 h, SDL_Color drawColor) {
    
    window = SDL_CreateWindow(
        "Starship Fontana",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        throw SFException("Failed to create window");
    }
    
    renderer = SDL_CreateRenderer(window, FIRST_SUPPORTED, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        throw SFException("Failed to create renderer");
    }

    SDL_SetRenderDrawColor(renderer, drawColor.r, drawColor.g, drawColor.b, drawColor.a);
}

SFWindow::~SFWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Window* SFWindow::getWindow() {
    return window;
}

SDL_Renderer* SFWindow::getRenderer() {
    return renderer;
}
