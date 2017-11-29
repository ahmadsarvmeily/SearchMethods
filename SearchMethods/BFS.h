#pragma once
#include "BlockGrid.h"
#include "TreeSearch.h"
#include <deque>
#include <memory>

class BFS {

public:
	static bool Search(const BlockGrid& root) {

		if (root.IsInGoalState()) return true;

		std::deque<Node> fringe;
		fringe.push_back({ root,0 });

		int nodes = 0;

		while (!fringe.empty()) {
			const Node& front = fringe.front();
			if (front.grid.IsInGoalState()) {
				PrintDetails(front, root, nodes, fringe.size());
				return true;
			}

			std::vector<Move> moves = front.grid.GetMoves();

			for (const Move& move : moves) {
				fringe.push_back({ front,move });
			}

			fringe.pop_front();
			nodes++;
		}
		return false;
	}
	
};