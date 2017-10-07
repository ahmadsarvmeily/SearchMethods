#include "BlockGrid.h"
#include <vector>
#include <iostream>

int main()
{
	BlockGrid grid(4, 4, { {3,0},{3,1},{3,2} }, { {1,1},{2,1},{3,1} }, {3,3});

	grid.PrintState();

	while (true) {

		std::vector<Move> moves = grid.GetMoves();

		std::cout << "Available moves:" << std::endl;
		for (const Move& move : moves) {
			switch (move) {
			case Move::Left:
				std::cout << "-(l)eft" << std::endl; break;
			case Move::Right:
				std::cout << "-(r)ight" << std::endl; break;
			case Move::Up:
				std::cout << "-(u)p" << std::endl; break;
			case Move::Down:
				std::cout << "-(d)own" << std::endl; break;
			}
		}
	
		char response;
		std::cin >> response;

		switch (response) {
		case 'l':
			grid.MoveAgent(Move::Left);
			break;
		case 'r':
			grid.MoveAgent(Move::Right);
			break;
		case 'u':
			grid.MoveAgent(Move::Up);
			break;
		case 'd':
			grid.MoveAgent(Move::Down);
			break;
		}
		grid.PrintState();
		if (grid.IsInGoalState()) {
			std::cout << "congrats" << std::endl;
			break;
		}
	}

    return 0;
}