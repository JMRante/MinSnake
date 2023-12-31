#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>
#include "gameEnums.h"
#include "gameState.h"
#include "gameRenderer.h"
#include "gameLevels.h"

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

	int current_level = 0;

	GameState state;
	state.reload_from_state(&levels[current_level]);

	SDL_Event event;

	bool is_game_running = true;

	Direction last_input_direction = state.get_snake_direction();

	int last_time = 0;
	int delta_time = 0;

	int move_timer = state.get_game_speed();

	while (is_game_running) {
		Uint32 ticks = SDL_GetTicks();
		delta_time = ticks - last_time;
		last_time = ticks;

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				is_game_running = false;
				break;
			case SDL_KEYDOWN:
				if (state.get_game_phase() == Lost) {
					state.reload_from_state(&levels[current_level]);
					last_input_direction = state.get_snake_direction();
				} else if (state.get_game_phase() == Won) {
					if (current_level < levels.size() - 1) {
						current_level++;
					} else {
						current_level = 0;
					}

					state.reload_from_state(&levels[current_level]);
					last_input_direction = state.get_snake_direction();
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

		if (move_timer == 0) {
			state.set_snake_direction(last_input_direction);
			state.move_snake();
			game_renderer.render(&state);

			move_timer = state.get_game_speed();
		}

		move_timer -= delta_time;

		if (move_timer < 0) {
			move_timer = 0;
		}
	}

	SDL_DestroyRenderer(sdl_renderer);

	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}