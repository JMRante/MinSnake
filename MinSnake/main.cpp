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
		300,
		10,
		10,
		{
			{ 10, 9 },
			{ 9, 9 },
			{ 8, 9 }
		},
		Right
	};

	GameState state;
	state.reload_from_state(&level);

	SDL_Event event;

	bool is_game_running = true;

	Direction last_input_direction = state.get_snake_direction();

	int game_speed = state.get_game_speed();
	int last_interval_time = game_speed + 1;

	while (is_game_running) {
		Uint32 ticks = SDL_GetTicks();
		int interval_time = ticks % game_speed;

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				is_game_running = false;
				break;
			case SDL_KEYDOWN:
				if (state.get_game_phase() == Lost) {
					state.reload_from_state(&level);
				} else {
					switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
						last_input_direction = Right;
						break;
					case SDLK_UP:
						last_input_direction = Up;
						break;
					case SDLK_LEFT:
						last_input_direction = Left;
						break;
					case SDLK_DOWN:
						last_input_direction = Down;
						break;
					}
				}
			}
		}

		if (interval_time < last_interval_time) {
			state.set_snake_direction(last_input_direction);
			state.move_snake();
			game_renderer.render(&state);
			game_speed = state.get_game_speed();

			last_interval_time = 0;
		} else {
			last_interval_time = interval_time;
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}