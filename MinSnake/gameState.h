#pragma once
#include <vector>
#include <utility>
#include <SDL.h>
#include "gameEnums.h"

using namespace std;

const int LEVELS_WIDTH = 20;
const int LEVELS_HEIGHT = 15;

class GameState
{
public:
	GameState() {};
	GameState(vector<int> level, SDL_Color background_color, SDL_Color wall_color, SDL_Color fruit_color, int start_speed, int speed_increment, int fruit_goal, vector<pair<int, int>> snake_positions, Direction snake_direction) :
		level(level), 
		background_color(background_color),
		wall_color(wall_color),
		fruit_color(fruit_color),
		start_speed(start_speed),
		speed_increment(speed_increment), 
		fruit_goal(fruit_goal), 
		snake_positions(snake_positions), 
		snake_direction(snake_direction) {
		phase = Play;
		game_speed = start_speed;
		fruits_eaten = 0;
		fruit_position = { 0, 0 };
	};
	~GameState() {};
	void reload_from_state(GameState* other_state);
	GameTile get_level_tile(int x, int y);
	void place_new_fruit();
	GamePhase move_snake();
	GamePhase get_game_phase();
	SDL_Color get_background_color();
	SDL_Color get_wall_color();
	SDL_Color get_fruit_color();
	int get_game_speed();
	pair<int, int> get_fruit_position();
	vector<pair<int, int>>* get_snake_positions();
	void set_snake_direction(Direction direction);
	Direction get_snake_direction();
private:
	vector<int> level;
	GamePhase phase;
	SDL_Color background_color;
	SDL_Color wall_color;
	SDL_Color fruit_color;
	int start_speed;
	int speed_increment;
	int game_speed;
	int fruits_eaten;
	int fruit_goal;
	pair<int, int> fruit_position;
	vector<pair<int, int>> snake_positions;
	Direction snake_direction;
};

