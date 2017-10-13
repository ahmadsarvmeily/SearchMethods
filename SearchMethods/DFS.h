#pragma once
#include "BlockGrid.h"
#include <stack>

class DFS {

public:
	static bool Search(const BlockGrid& root, int limit = -1) {

		if (root.IsInGoalState()) return true;

		std::stack<BlockGrid> states;
		states.emplace(root);

		for (int depth = 0; !states.empty() && (depth < limit || limit == -1); depth++) {
			BlockGrid currentState = states.top();
			states.pop();

			for (const Move& move : currentState.GetMovesShuffled()) {
				BlockGrid grid = currentState;
				if (grid.MoveAgent(move).IsInGoalState()) {
					return true;
				}
				states.push(grid);	
			}
		}
		return false;
	}
};