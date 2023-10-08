#include "gameRenderer.h"

void GameRenderer::render(GameState* game_state) {
	render_background(game_state->get_background_color());

	SDL_Color snake_body_color = SNAKE_BODY_COLOR;

	switch (game_state->get_game_phase()) {
	case Lost: snake_body_color = SNAKE_BODY_LOST_COLOR; break;
	case Won: snake_body_color = SNAKE_BODY_WON_COLOR; break;
	default: snake_body_color = SNAKE_BODY_COLOR; break;
	}

	// Render level
	for (int i = 0; i < LEVELS_WIDTH; i++) {
		for (int j = 0; j < LEVELS_HEIGHT; j++) {
			switch (game_state->get_level_tile(i, j)) {
			case Blank: break;
			case Wall:
				render_wall(i, j, game_state->get_wall_color());
				break;
			default: break;
			}
		}
	}

	// Render Fruit
	render_fruit(game_state->get_fruit_position().first, game_state->get_fruit_position().second, game_state->get_fruit_color());

	// Render snake
	bool is_first_segment = true;

	for (const pair<int, int> segment : *game_state->get_snake_positions()) {
		if (is_first_segment) {
			render_snake_head(segment.first, segment.second, game_state->get_snake_direction(), snake_body_color, SNAKE_EYE_COLOR);
			is_first_segment = false;
		} else {
			render_snake_body(segment.first, segment.second, snake_body_color);
		}
	}

	SDL_RenderPresent(sdl_renderer);
}

void GameRenderer::render_circle(int x, int y, int w, int h, int sides, SDL_Color color) {
	vector<SDL_Vertex> vertices;

	float angle = 0;
	float radian_increment = (2.0f * (float)M_PI) / (float)sides;
	SDL_FPoint center_point = { x + ((float)w / 2.0f), y + ((float)h / 2.0f) };
	SDL_FPoint last_point = { center_point.x + ((float)w / 2.0f), center_point.y };

	while (angle <= 2.0f * (float)M_PI) {
		angle += radian_increment;
		float x_adjust = (float)cos(angle) * ((float)w / 2.0f);
		float y_adjust = -(float)sin(angle) * ((float)h / 2.0f);
		SDL_FPoint next_point = { center_point.x + x_adjust, center_point.y + y_adjust };

		vertices.push_back({ center_point, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ next_point, { color.r, color.g, color.b, color.a }, { 0, 0 } });
		vertices.push_back({ last_point, { color.r, color.g, color.b, color.a }, { 0, 0 } });

		last_point = next_point;
	}

	SDL_RenderGeometry(sdl_renderer, nullptr, vertices.data(), (int)vertices.size(), nullptr, 0);
}

void GameRenderer::render_background(SDL_Color color) {
	SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(sdl_renderer);
}

void GameRenderer::render_wall(int grid_x, int grid_y, SDL_Color color) {
	const int PADDING = 2;

	SDL_Rect rect;
	rect.x = (grid_x * TILE_WIDTH) + PADDING;
	rect.y = (grid_y * TILE_HEIGHT) + PADDING;
	rect.w = TILE_WIDTH - (PADDING * 2);
	rect.h = TILE_HEIGHT - (PADDING * 2);

	SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(sdl_renderer, &rect);
}

void GameRenderer::render_fruit(int grid_x, int grid_y, SDL_Color color) {
	const int PADDING = 8;

	render_circle((grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 24, { color.r, color.g, color.b, color.a });
}

void GameRenderer::render_snake_head(int grid_x, int grid_y, Direction direction, SDL_Color head_color, SDL_Color eye_color) {
	render_snake_body(grid_x, grid_y, head_color);

	const int PADDING = 8;
	const int EYE_SIZE = 16;

	switch (direction) {
	case Right:
		render_circle(((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, eye_color);
		render_circle(((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, eye_color);
		break;
	case Up:
		render_circle(((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 20, eye_color);
		render_circle((grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, eye_color);
		break;
	case Left:
		render_circle((grid_x * TILE_WIDTH) + PADDING, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, eye_color);
		render_circle((grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, EYE_SIZE, EYE_SIZE, 8, eye_color);
		break;
	case Down:
		render_circle((grid_x * TILE_WIDTH) + PADDING, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 20, eye_color);
		render_circle(((grid_x + 1) * TILE_WIDTH) - PADDING - EYE_SIZE, ((grid_y + 1) * TILE_HEIGHT) - PADDING - EYE_SIZE, EYE_SIZE, EYE_SIZE, 8, eye_color);
		break;
	}
}

void GameRenderer::render_snake_body(int grid_x, int grid_y, SDL_Color color) {
	const int PADDING = 2;

	render_circle((grid_x * TILE_WIDTH) + PADDING, (grid_y * TILE_HEIGHT) + PADDING, TILE_WIDTH - (PADDING * 2), TILE_HEIGHT - (PADDING * 2), 32, color);
}
