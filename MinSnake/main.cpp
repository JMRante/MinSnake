#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>
#include "gameEnums.h"
#include "gameState.h"

using namespace std;

const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;

void render_circle(SDL_Renderer* renderer, int x, int y, int w, int h, int sides, SDL_Color color) {
	vector<SDL_Vertex> vertices;

	float angle = 0;
	float radian_increment = (2.0f * (float)M_PI) / (float)sides;
	SDL_FPoint center_point = { x + ((float)w / 2.0f), y + ((float)h / 2.0f) };
	SDL_FPoint last_point = { center_point.x + ((float)w / 2.0f), center_point.y };

	while (angle <= 2.0f * (float)M_PI) {
		angle += radian_increment;
		float x_adjust = cos(angle) * ((float)w / 2.0f);
		float y_adjust = -sin(angle) * ((float)h / 2.0f);
		SDL_FPoint next_point = { center_point.x + x_adjust, center_point.y + y_adjust };

		vertices.push_back({ center_point, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ next_point, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ last_point, { color.r, color.g, color.b, color.a }, { 0, 0 } });

		last_point = next_point;
	}

	SDL_RenderGeometry(renderer, nullptr, vertices.data(), (int)vertices.size(), nullptr, 0);
}

void render_background(SDL_Renderer* renderer, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

void render_wall(SDL_Renderer* renderer, int grid_x, int grid_y, SDL_Color color) {
	const int PADDING = 2;

	SDL_Rect rect;
	rect.x = (grid_x * TILE_WIDTH) + PADDING;
	rect.y = (grid_y * TILE_HEIGHT) + PADDING;
	rect.w = TILE_WIDTH - (PADDING * 2);
	rect.h = TILE_HEIGHT - (PADDING * 2);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void render_snake_body(SDL_Renderer* renderer, int grid_x, int grid_y) {
	const int PADDING = 2;

	render_circle(renderer, (grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 32, { 0, 204, 153, 255 });
}

void render_snake_head(SDL_Renderer* renderer, int grid_x, int grid_y, Direction direction) {
	render_snake_body(renderer, grid_x, grid_y);

	const int PADDING = 8;
	const int EYE_SIZE = 16;

	switch (direction) {
	case Right:
		render_circle(renderer, ((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, ((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Up:
		render_circle(renderer, ((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, (grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Left:
		render_circle(renderer, (grid_x * TILE_WIDTH) + PADDING, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, (grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Down:
		render_circle(renderer, (grid_x * TILE_WIDTH) + PADDING, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, ((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	}
}

void render_fruit(SDL_Renderer* renderer, int grid_x, int grid_y, SDL_Color color) {
	const int PADDING = 8;

	render_circle(renderer, (grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 24, { color.r, color.g, color.b, color.a });
}

void render(GameState game_state, SDL_Renderer* renderer) {
	render_background(renderer, { 0, 0, 153, 255 });

	for (int i = 0; i < LEVELS_WIDTH; i++) {
		for (int j = 0; j < LEVELS_HEIGHT; j++) {
			switch (game_state.get_level_tile(i, j)) {
			case Blank: break;
			case Wall:
				render_wall(renderer, i, j, { 0, 153, 255, 255 });
				break;
			case Fruit:
				render_fruit(renderer, i, j, { 255, 51, 153, 255 });
				break;
			case SnakeBody:
				render_snake_body(renderer, i, j);
				break;
			case SnakeHeadRight:
				render_snake_head(renderer, i, j, Right);
				break;
			case SnakeHeadUp:
				render_snake_head(renderer, i, j, Up);
				break;
			case SnakeHeadLeft:
				render_snake_head(renderer, i, j, Left);
				break;
			case SnakeHeadDown:
				render_snake_head(renderer, i, j, Down);
				break;
			default: break;
			}
		}
	}

	SDL_RenderPresent(renderer);
}

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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		cout << "Failed to create renderer: " << SDL_GetError() << "\n";
		return 1;
	}

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
			render(level, renderer);
		}

		last_interval_time = interval_time;
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}