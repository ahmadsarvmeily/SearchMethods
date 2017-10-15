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
			while (!states.empty()) {
				Node currentState = states.top();
				states.pop();

				for (const Move& move : currentState.grid.GetMovesShuffled()) {
					Node node = currentState;
					node.depth++;
					if (node.grid.MoveAgent(move).IsInGoalState()) {
						std::cout << node.depth << std::endl;
						return true;
					}
					if (node.depth < limit || limit == -1) {
						states.push(node);
					}
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