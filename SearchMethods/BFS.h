#pragma once
#include "BlockGrid.h"
#include <deque>

class BFS {

public:
	static bool Search(const BlockGrid& root) {

		if (root.IsInGoalState()) return true;

		std::deque<BlockGrid> states;
		states.push_back(root);

		while (!states.empty()) {
			BlockGrid& currentState = states.front();
			
			for (const Move& move : currentState.GetMoves()) {
				BlockGrid grid = currentState;
				if (grid.MoveAgent(move).IsInGoalState()) {
					return true;
				}
				states.push_back(std::move(grid));
			}
			states.pop_front();
		}
		return false;
	}
};