#include <iostream>
#include <vector>
#include <SDL.h>

using namespace std;

void render(int level[15][20], SDL_Renderer* renderer) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 15; j++) {
			if (level[j][i] == 1) {
				SDL_Rect rect;
				rect.x = (i * 50) + 2;
				rect.y = (j * 50) + 2;
				rect.w = 50 - 4;
				rect.h = 50 - 4;

				SDL_SetRenderDrawColor(renderer, 0, 153, 255, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
		}
	}
}

int main(int argc, char** args) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Failed to start SDL: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("MinSnake", 100, 100, 1000, 750, SDL_WINDOW_SHOWN);

	if (!window) {
		cout << "Failed to create window: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		cout << "Failed to create renderer: " << SDL_GetError() << "\n";
		return 1;
	}

	int level[15][20] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	bool is_game_running = true;

	while (is_game_running) {
		Uint32 ticks = SDL_GetTicks();

		if (ticks % 100 == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255);
			SDL_RenderClear(renderer);

			render(level, renderer);

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