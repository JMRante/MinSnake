#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>

using namespace std;

const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;

enum Direction { Right, Up, Left, Down };
enum GameTiles { Blank, Wall, Fruit, SnakeBody, SnakeHeadRight, SnakeHeadUp, SnakeHeadLeft, SnakeHeadDown };

void renderCircle(SDL_Renderer* renderer, int x, int y, int w, int h, int sides, SDL_Color color) {
	vector<SDL_Vertex> vertices;

	float angle = 0;
	float radianIncrement = (2.0f * (float)M_PI) / (float)sides;
	SDL_FPoint centerPoint = { x + ((float)w / 2.0f), y + ((float)h / 2.0f) };
	SDL_FPoint lastPoint = { centerPoint.x + ((float)w / 2.0f), centerPoint.y };

	while (angle <= 2.0f * (float)M_PI) {
		angle += radianIncrement;
		float xAdjust = cos(angle) * ((float)w / 2.0f);
		float yAdjust = -sin(angle) * ((float)h / 2.0f);
		SDL_FPoint nextPoint = { centerPoint.x + xAdjust, centerPoint.y + yAdjust };

		vertices.push_back({ centerPoint, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ nextPoint, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ lastPoint, { color.r, color.g, color.b, color.a }, { 0, 0 } });

		lastPoint = nextPoint;
	}

	SDL_RenderGeometry(renderer, nullptr, vertices.data(), (int)vertices.size(), nullptr, 0);
}

void renderWall(SDL_Renderer* renderer, int gridX, int gridY, SDL_Color color) {
	const int PADDING = 2;

	SDL_Rect rect;
	rect.x = (gridX * TILE_WIDTH) + PADDING;
	rect.y = (gridY * TILE_HEIGHT) + PADDING;
	rect.w = TILE_WIDTH - (PADDING * 2);
	rect.h = TILE_HEIGHT - (PADDING * 2);

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);
}

void renderSnakeBody(SDL_Renderer* renderer, int gridX, int gridY) {
	const int PADDING = 2;

	renderCircle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 32, { 0, 204, 153, 255 });
}

void renderSnakeHead(SDL_Renderer* renderer, int gridX, int gridY, Direction direction) {
	renderSnakeBody(renderer, gridX, gridY);

	const int PADDING = 8;
	const int EYE_SIZE = 16;

	switch (direction) {
	case Right:
		renderCircle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		renderCircle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Up:
		renderCircle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		renderCircle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Left:
		renderCircle(renderer, (gridX * TILE_WIDTH) + PADDING, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		renderCircle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	case Down:
		renderCircle(renderer, (gridX * TILE_WIDTH) + PADDING, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, { 26, 26, 26, 255 });
		renderCircle(renderer, ((gridX + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((gridY + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, { 26, 26, 26, 255 });
		break;
	}
}

void renderFruit(SDL_Renderer* renderer, int gridX, int gridY, SDL_Color color) {
	const int PADDING = 8;

	renderCircle(renderer, (gridX * TILE_WIDTH) + PADDING, (gridY * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 24, { color.r, color.g, color.b, color.a });
}

void render(int level[15][20], SDL_Renderer* renderer) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 15; j++) {
			switch (level[j][i]) {
			case Blank: break;
			case Wall:
				renderWall(renderer, i, j, { 0, 153, 255, 255 });
				break;
			case Fruit:
				renderFruit(renderer, i, j, { 255, 51, 153, 255 });
				break;
			case SnakeBody:
				renderSnakeBody(renderer, i, j);
				break;
			case SnakeHeadRight:
				renderSnakeHead(renderer, i, j, Right);
				break;
			case SnakeHeadUp:
				renderSnakeHead(renderer, i, j, Up);
				break;
			case SnakeHeadLeft:
				renderSnakeHead(renderer, i, j, Left);
				break;
			case SnakeHeadDown:
				renderSnakeHead(renderer, i, j, Down);
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
		1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,5,0,6,0,7,0,0,0,0,1,
		1,0,0,0,1,1,0,3,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,1,1,0,3,0,0,0,0,0,1,1,1,0,0,0,1,
		1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,3,3,3,4,0,0,0,2,0,0,0,0,1,
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

		if (ticks == 10000) {
			is_game_running = false;
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}