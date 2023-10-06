#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>

using namespace std;

void renderCircle(SDL_Renderer* renderer, int x, int y, int w, int h, int sides, SDL_Color color) {
	vector<SDL_Vertex> vertices;

	float angle = 0;
	float radianIncrement = (2.0f * M_PI) / (float)sides;
	SDL_FPoint centerPoint = { x + ((float)w / 2.0f), y + ((float)h / 2.0f) };
	SDL_FPoint lastPoint = { centerPoint.x + ((float)w / 2.0f), centerPoint.y };

	while (angle <= 2.0f * M_PI) {
		angle += radianIncrement;
		float xAdjust = cos(angle) * ((float)w / 2.0f);
		float yAdjust = -sin(angle) * ((float)h / 2.0f);
		SDL_FPoint nextPoint = { centerPoint.x + xAdjust, centerPoint.y + yAdjust };

		vertices.push_back({ centerPoint, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ nextPoint, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ lastPoint, { color.r, color.g, color.b, color.a }, { 0, 0 } });

		lastPoint = nextPoint;
	}

	SDL_RenderGeometry(renderer, nullptr, vertices.data(), vertices.size(), nullptr, 0);
}

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
			} else if (level[j][i] == 2) {
				renderCircle(renderer, (i * 50) + 4, (j * 50) + 4, 50 - 8, 50 - 8, 32, { 255, 0, 102, 255 });
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
		1,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
		1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
		1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,
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