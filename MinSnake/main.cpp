#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>

using namespace std;

const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;

enum Direction { Right, Up, Left, Down };
enum GameTiles { Blank, Wall, Fruit, SnakeBody, SnakeHeadRight, SnakeHeadUp, SnakeHeadLeft, SnakeHeadDown };

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

void render_wall(SDL_Renderer* renderer, int gridX, int gridY, SDL_Color color) {
	const int PADDING = 2;

	SDL_Rect rect;
	rect.x = (gridX * TILE_WIDTH) + PADDING;
	rect.y = (gridY * TILE_HEIGHT) + PADDING;
	rect.w = TILE_WIDTH - (PADDING * 2);
	rect.h = TILE_HEIGHT - (PADDING * 2);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void render_snake_body(SDL_Renderer* renderer, int gridX, int gridY) {
	const int PADDING = 2;

	render_circle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 32, { 0, 204, 153, 255 });
}

void render_snake_head(SDL_Renderer* renderer, int gridX, int gridY, Direction direction) {
	render_snake_body(renderer, gridX, gridY);

	const int PADDING = 8;
	const int EYE_SIZE = 16;

	switch (direction) {
	case Right:
		render_circle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Up:
		render_circle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Left:
		render_circle(renderer, (gridX * TILE_WIDTH) + PADDING, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Down:
		render_circle(renderer, (gridX * TILE_WIDTH) + PADDING, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		render_circle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	}
}

void render_fruit(SDL_Renderer* renderer, int gridX, int gridY, SDL_Color color) {
	const int PADDING = 8;

	render_circle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 24, { color.r, color.g, color.b, color.a });
}

void render(int level[15][20], SDL_Renderer* renderer) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 15; j++) {
			switch (level[j][i]) {
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
}

int main(int argc, char** args) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Failed to start SDL: " << SDL_GetError() << "\n";
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("MinSnake", 100, 100, 20 * TILE_WIDTH, 15 * TILE_HEIGHT, SDL_WINDOW_SHOWN);

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

	SDL_Event event;

	bool is_game_running = true;

	while (is_game_running) {
		Uint32 ticks = SDL_GetTicks();

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				is_game_running = false;
				break;
			}
		}

		if (ticks % 100 == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255);
			SDL_RenderClear(renderer);

			render(level, renderer);

			SDL_RenderPresent(renderer);
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}