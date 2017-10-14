#pragma once
#include "BlockGrid.h"
#include <stack>

class DFS {

public:
	static bool Search(const BlockGrid& root, int limit = -1) {

		if (root.IsInGoalState()) return true;

		std::stack<Node> states;
		states.push({ root,0 });

		if (limit > 0 || limit == -1) {
			for (int depth = 0; !states.empty(); depth++) {
				Node currentState = states.top();
				states.pop();

				for (const Move& move : currentState.grid.GetMovesShuffled()) {
					BlockGrid grid = currentState.grid;
					if (grid.MoveAgent(move).IsInGoalState()) {
						std::cout << currentState.depth + 1 << std::endl;
						return true;
					}
					if (currentState.depth < limit || limit == -1)
						states.push({ grid,currentState.depth + 1 });
				}

			}
		}
		return false;
	}

	class Node {

	public:
		Node(BlockGrid grid, int depth) :
			grid(grid),
			depth(depth) {}

		BlockGrid grid;
		int depth;
	};
};