#include <vector>
#include <utility>
#include <random>
#include "gameState.h"

void GameState::reload_from_state(GameState* other_state) {
	level = other_state->level;
	phase = other_state->phase;
	background_color = other_state->background_color;
	wall_color = other_state->wall_color;
	fruit_color = other_state->fruit_color;
	start_speed = other_state->start_speed;
	speed_increment = other_state->speed_increment;
	game_speed = other_state->game_speed;
	fruits_eaten = other_state->fruits_eaten;
	fruit_goal = other_state->fruit_goal;
	fruit_position = other_state->fruit_position;
	snake_positions = other_state->snake_positions;
	snake_direction = other_state->snake_direction;

	place_new_fruit();
}

GameTile GameState::get_level_tile(int x, int y) {
	return (GameTile)level[x + (y * LEVELS_WIDTH)];
}

void GameState::place_new_fruit() {
	vector<pair<int, int>> valid_fruit_positions;

	int x = 0;
	int y = 0;

	for (int x = 0; x < LEVELS_WIDTH; x++) {
		for (int y = 0; y < LEVELS_HEIGHT; y++) {
			GameTile tile = get_level_tile(x, y);

			// Check if tile is blank, not on a snake segment, and far enough from the head
			if (tile == Blank) {
				bool overlaps_snake = false;

				for (pair<int, int> segment_position : snake_positions) {
					if (segment_position.first == x && segment_position.second == y) {
						overlaps_snake = true;
						break;
					}
				}

				if (!overlaps_snake) {
					int x_distance_to_head = abs(snake_positions[0].first - x);
					int y_distance_to_head = abs(snake_positions[0].second - y);

					if (x_distance_to_head > 4 && y_distance_to_head > 4) {
						valid_fruit_positions.push_back({ x, y });
					}
				}
			}

			// Calculate next tile position
			if (x < LEVELS_WIDTH) {
				x++;
			}
			else {
				x = 0;
				y++;
			}
		}
	}

	// Randomly choose a valid fruit position
	random_device device;
	mt19937 random_generator(device());
	uniform_int_distribution<mt19937::result_type> position_distribution(1, (int)valid_fruit_positions.size());

	fruit_position = valid_fruit_positions[position_distribution(random_generator) - 1];
}

void GameState::set_snake_direction(Direction direction) {
	if (phase == Lost || phase == Won ||
		(direction == Right && snake_direction == Left) ||
		(direction == Left && snake_direction == Right) ||
		(direction == Up && snake_direction == Down) ||
		(direction == Down && snake_direction == Up)) {
		return;
	}

	snake_direction = direction;
}

GamePhase GameState::move_snake() {
	if (phase == Lost || phase == Won) {
		return phase;
	}

	pair<int, int> last_segments_position = { -1, -1 };

	for (pair<int, int> &segment_position : snake_positions) {
		if (last_segments_position == make_pair(-1, -1)) {
			last_segments_position = segment_position;

			// Move head in new direction
			switch (snake_direction) {
			case Right: segment_position.first = segment_position.first + 1; break;
			case Up: segment_position.second = segment_position.second - 1; break;
			case Left: segment_position.first = segment_position.first - 1; break;
			case Down: segment_position.second = segment_position.second + 1; break;
			}

			// Check if head is hitting a wall
			if (get_level_tile(segment_position.first, segment_position.second) == Wall) {
				phase = Lost;
			}
		} else {
			pair<int, int> temp_segment_position = segment_position;

			// Move body segment to position of the segment ahead of it
			segment_position.first = last_segments_position.first;
			segment_position.second = last_segments_position.second;

			last_segments_position = temp_segment_position;

			// Check if head is hitting body segment
			if (snake_positions[0] == segment_position) {
				phase = Lost;
			}
		}
	}

	// Check if head is touching fruit
	if (snake_positions[0] == fruit_position) {
		fruits_eaten++;

		// If more fruits to eat, place a new fruit and grow snake
		// Otherwise, return win state
		if (fruits_eaten < fruit_goal) {
			place_new_fruit();
			game_speed -= speed_increment;
			snake_positions.push_back(last_segments_position);
		} else {
			phase = Won;
		}
	}

	return phase;
}

GamePhase GameState::get_game_phase() {
	return phase;
}

SDL_Color GameState::get_background_color() {
	return background_color;
}

SDL_Color GameState::get_wall_color() {
	return wall_color;
}

SDL_Color GameState::get_fruit_color() {
	return fruit_color;
}

int GameState::get_game_speed() {
	return game_speed;
}

pair<int, int> GameState::get_fruit_position() {
	return fruit_position;
}

vector<pair<int, int>>* GameState::get_snake_positions() {
	return &snake_positions;
}

Direction GameState::get_snake_direction() {
	return snake_direction;
}