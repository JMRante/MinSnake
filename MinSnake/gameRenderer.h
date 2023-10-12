#pragma once
#include <SDL.h>
#include "gameState.h"

const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;

const SDL_Color SNAKE_BODY_COLOR = { 0, 204, 153, 255 };
const SDL_Color SNAKE_EYE_COLOR = { 26, 26, 26, 255 };
const SDL_Color SNAKE_BODY_LOST_COLOR = { 255, 80, 80 };
const SDL_Color SNAKE_BODY_WON_COLOR = { 255, 204, 0, 255 };

class GameRenderer
{
public:
	GameRenderer(SDL_Renderer* sdl_renderer): sdl_renderer(sdl_renderer) {};
	~GameRenderer() {};
	void render(GameState* game_state);
private:
	SDL_Renderer* sdl_renderer;
	void render_circle(int x, int y, int w, int h, int sides, SDL_Color color);
	void render_background(SDL_Color color);
	void render_wall(int grid_x, int grid_y, SDL_Color color);
	void render_fruit(int grid_x, int grid_y, SDL_Color color);
	void render_snake_head(int grid_x, int grid_y, Direction direction, SDL_Color head_color, SDL_Color eye_color);
	void render_snake_body(int grid_x, int grid_y, SDL_Color color);
};

