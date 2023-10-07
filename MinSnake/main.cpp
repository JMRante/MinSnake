#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>
#include "gameEnums.h"
#include "gameState.h"
#include "gameRenderer.h"

using namespace std;

int main(int argc, char** args) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Failed to start SDL: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("MinSnake", 100, 100, LEVELS_WIDTH * TILE_WIDTH, LEVELS_HEIGHT * TILE_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) {
		cout << "Failed to create window: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	if (!sdl_renderer) {
		cout << "Failed to create renderer: " << SDL_GetError() << "\n";
		return 1;
	}

	GameRenderer game_renderer(sdl_renderer);

	GameState level = {
		{
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
		},
		{ 0, 0, 153, 255 },
		{ 51, 102, 255, 255 },
		{ 255, 0, 102, 255 },
		500,
		10,
		10,
		{
			{ 10, 9 },
			{ 9, 9 },
			{ 8, 9 }
		},
		Right
	};

	SDL_Event event;

	bool is_game_running = true;

	int game_speed = 500;
	int last_interval_time = game_speed + 1;

	while (is_game_running) {
		Uint32 ticks = SDL_GetTicks();
		int interval_time = ticks % game_speed;

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				is_game_running = false;
				break;
			}
		}

		if (interval_time < last_interval_time) {
			game_renderer.render(&level);
		}

		last_interval_time = interval_time;
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}