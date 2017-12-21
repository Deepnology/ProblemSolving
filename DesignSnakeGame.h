#ifndef DESIGN_SNAKE_GAME_H
#define DESIGN_SNAKE_GAME_H
#include "Debug.h"
/*
Leetcode: Design Snake Game
Design a Snake game that is played on a device with screen size = width x height.
The snake is initially positioned at the top left corner (0,0) with length = 1 unit.
You are given a list of food¡¦s positions in row-column order.
When a snake eats the food, its length and the game¡¦s score both increase by 1.
Each food appears one by one on the screen.
For example, the second food will not appear until the first food was eaten by the snake.
When a food does appear on the screen, it is guaranteed that it will not appear on a block occupied by the snake.
Example:
Given width = 3, height = 2, and food = [[1,2],[0,1]].
Snake snake = new Snake(width, height, food);
Initially the snake appears at position (0,0) and the food at (1,2).
|S| | |
| | |F|
snake.move(¡§R¡¨); -> Returns 0
| |S| |
| | |F|
snake.move(¡§D¡¨); -> Returns 0
| | | |
| |S|F|
snake.move(¡§R¡¨); -> Returns 1 (Snake eats the first food and right after that, the second food appears at (0,1) )
| |F| |
| |S|S|
snake.move(¡§U¡¨); -> Returns 1
| |F|S|
| | |S|
snake.move(¡§L¡¨); -> Returns 2 (Snake eats the second food)
| |S|S|
| | |S|
snake.move(¡§U¡¨); -> Returns -1 (Game over because snake collides with border)

*/
class DesignSnakeGame
{
public:
	/** Initialize your data structure here.
	@param width - screen width
	@param height - screen height
	@param food - A list of food positions
	E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
	DesignSnakeGame(int width, int height, std::vector<std::pair<int, int>> food):
		m_width(width), m_height(height), m_food(food), m_score(0), m_snake()
	{
		m_snake.push_back({ 0,0 });//head
	}
	~DesignSnakeGame() {}

	/** Moves the snake.
	@param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down
	@return The game's score after the move. Return -1 if game over.
	Game over when snake crosses the screen boundary or bites its body. */
	int move(const std::string & direction)
	{
		auto head = m_snake.front();
		auto tail = m_snake.back();
		m_snake.pop_back();
		if (direction == "U") --head.first;
		else if (direction == "D") ++head.first;
		else if (direction == "L") --head.second;
		else if (direction == "R") ++head.second;

		if (head.first < 0 || head.first > m_height - 1 || head.second < 0 || head.second > m_width - 1 || // hit boundary
			std::count(m_snake.begin(), m_snake.end(), head)) // hit snake body
		{
			m_score = -1;
		}
		else
		{
			m_snake.insert(m_snake.begin(), head);
			if (!m_food.empty() && head == m_food.front())
			{
				m_food.erase(m_food.begin());
				m_snake.push_back(tail);
				++m_score;
			}
		}

		std::cout << "DesignSnakeGame move \"" << direction << "\": " << Debug::ToStr1D<int>()(m_snake) << " , score=" << m_score << std::endl;
		return m_score;
	}

private:
	int m_width;
	int m_height;
	int m_score;
	std::vector<std::pair<int, int>> m_food;
	std::vector<std::pair<int, int>> m_snake;
};
/**
* Your SnakeGame object will be instantiated and called as such:
* SnakeGame obj = new SnakeGame(width, height, food);
* int param_1 = obj.move(direction);
*/

/*
DesignSnakeGame move "R": [0,1] , score=0
DesignSnakeGame move "D": [1,1] , score=0
DesignSnakeGame move "R": [1,2], [1,1] , score=1
DesignSnakeGame move "U": [0,2], [1,2] , score=1
DesignSnakeGame move "L": [0,1], [0,2], [1,2] , score=2
DesignSnakeGame move "L": [0,0], [0,1], [0,2] , score=2
DesignSnakeGame move "D": [1,0], [0,0], [0,1] , score=2
DesignSnakeGame move "D": [1,0], [0,0] , score=-1
*/
#endif
