#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char** args) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Failed to start SDL: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("MinSnake", 100, 100, 1000, 1000, SDL_WINDOW_SHOWN);

	if (!window) {
		cout << "Failed to create window: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		cout << "Failed to create renderer: " << SDL_GetError() << "\n";
		return 1;
	}

	bool is_game_running = true;

	while (is_game_running) {
		Uint32 ticks = SDL_GetTicks();

		if (ticks % 100 == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255);
			SDL_RenderClear(renderer);

			SDL_RenderPresent(renderer);
		}

		if (ticks == 5000) {
			is_game_running = false;
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}