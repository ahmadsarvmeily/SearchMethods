#pragma once
#include "BlockGrid.h"
#include <queue>

class BFS {

public:
	static void Search(const BlockGrid& root) {

		std::queue<BlockGrid> states;
		states.emplace(root);

		while (!states.empty()) {
			BlockGrid currentState = states.front();
			states.pop();
			
			for (const Move& move : currentState.GetMoves()) {
				BlockGrid grid = currentState;
				if (grid.MoveAgent(move).IsInGoalState()) {
					return;
				}
				states.push(grid);
			}
		}
	}
};