#pragma once

enum Direction { Right, Up, Left, Down };
enum GameTile { Blank, Wall, Fruit, SnakeBody, SnakeHeadRight, SnakeHeadUp, SnakeHeadLeft, SnakeHeadDown };
enum GamePhase { Play, Lost, Won };