#include <vector>
#include <utility>
#include <random>
#include "gameState.h"

GameTile GameState::get_level_tile(int x, int y) {
	return (GameTile)level[x + (y * LEVELS_WIDTH)];
}

void GameState::place_new_fruit() {
	vector<pair<int, int>> valid_fruit_positions;

	int x = 0;
	int y = 0;

	for (int tile : level) {
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
		} else {
			x = 0;
			y++;
		}
	}

	// Randomly choose a valid fruit position
	random_device device;
	mt19937 random_generator(device());
	uniform_int_distribution<mt19937::result_type> position_distribution(1, (int)valid_fruit_positions.size());

	fruit_position = valid_fruit_positions[position_distribution(random_generator)];
}

GamePhase GameState::move_snake(Direction direction) {
	pair<int, int> last_segments_position = { -1, -1 };

	for (pair<int, int> &segment_position : snake_positions) {
		if (last_segments_position == make_pair(-1, -1)) {
			// Move head in new direction
			switch (direction) {
			case Right: segment_position.first = segment_position.first + 1; break;
			case Up: segment_position.second = segment_position.second - 1; break;
			case Left: segment_position.first = segment_position.first - 1; break;
			case Down: segment_position.second = segment_position.second + 1; break;
			}

			// Check if head is hitting a wall
			if (get_level_tile(segment_position.first, segment_position.second) == Wall) {
				return Lost;
			}
		} else {
			// Move body segment to position of the segment ahead of it
			segment_position.first = last_segments_position.first;
			segment_position.second = last_segments_position.second;

			// Check if head is hitting body segment
			if (snake_positions[0] == segment_position) {
				return Lost;
			}
		}

		last_segments_position = segment_position;
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
			return Won;
		}
	}

	return Play;
}

int GameState::get_game_speed() {
	return game_speed;
}