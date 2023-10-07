#pragma once
#include <vector>
#include <utility>
#include "gameEnums.h"

using namespace std;

const int LEVELS_WIDTH = 20;
const int LEVELS_HEIGHT = 15;

class GameState
{
public:
	GameState(vector<int> level, int start_speed, int speed_increment, int fruit_goal, vector<pair<int, int>> snake_positions, Direction snake_direction) : 
		level(level), 
		start_speed(start_speed),
		speed_increment(speed_increment), 
		fruit_goal(fruit_goal), 
		snake_positions(snake_positions), 
		snake_direction(snake_direction) {
		game_speed = start_speed;
		fruits_eaten = 0;
		fruit_position = { 0, 0 };
	};
	~GameState() {};
	GameState(const GameState& rhs) { 
		level = rhs.level;
		start_speed = rhs.start_speed;
		speed_increment = rhs.speed_increment;
		game_speed = rhs.game_speed;
		fruits_eaten = rhs.fruits_eaten;
		fruit_goal = rhs.fruit_goal;
		fruit_position = rhs.fruit_position;
		snake_positions = rhs.snake_positions;
		snake_direction = rhs.snake_direction;
	}
	GameState& operator=(const GameState& rhs) {};
	GameTile get_level_tile(int x, int y);
	void place_new_fruit();
	GamePhase move_snake(Direction direction);
	int get_game_speed();
private:
	vector<int> level;
	int start_speed;
	int speed_increment;
	int game_speed;
	int fruits_eaten;
	int fruit_goal;
	pair<int, int> fruit_position;
	vector<pair<int, int>> snake_positions;
	Direction snake_direction;
};

