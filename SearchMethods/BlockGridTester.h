#pragma once
#include "BlockGrid.h"
#include <vector>
#include <iostream>

class BlockGridTester {

public:
	BlockGridTester(BlockGrid& blockGrid) :
		blockGrid(blockGrid) {}

	void Run() {
		while (true) {
			blockGrid.PrintState();
			std::vector<Move> moves = blockGrid.GetMoves();

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
				blockGrid.MoveAgent(Move::Left);
				break;
			case 'r':
				blockGrid.MoveAgent(Move::Right);
				break;
			case 'u':
				blockGrid.MoveAgent(Move::Up);
				break;
			case 'd':
				blockGrid.MoveAgent(Move::Down);
				break;
			}

			if (blockGrid.IsInGoalState()) {
				std::cout << "congrats" << std::endl;
				break;
			}
		}
	}

private:
	BlockGrid& blockGrid;
};