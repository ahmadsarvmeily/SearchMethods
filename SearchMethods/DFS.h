#pragma once
#include "BlockGrid.h"
#include <stack>

class DFS {

public:

	static void Search(const BlockGrid& root) {

		std::stack<BlockGrid> states;
		states.emplace(root);

		while (!states.empty()) {
			BlockGrid currentState = states.top();
			states.pop();

			for (const Move& move : currentState.GetMovesShuffled()) {
				BlockGrid grid = currentState;
				if (grid.MoveAgent(move).IsInGoalState()) {
					return;
				}
				states.push(grid);
			}
		}
	}
};