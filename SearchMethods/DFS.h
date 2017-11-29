#pragma once
#include "BlockGrid.h"
#include "TreeSearch.h"
#include <memory>

class DFS {

public:
	static bool Search(const BlockGrid& root) {
		return Search(root, true, -1);
	}

	static bool Search(const BlockGrid& root, bool randomMoves, int limit) {

		int nodes = 0;
		bool isDepthLimited = limit != -1;
		std::stack<Node> fringe;
		fringe.push({ root,0 });

		while (!fringe.empty()) {
			Node top = fringe.top();
			BlockGrid& grid = top.grid;
			if (grid.IsInGoalState()) {
				PrintDetails(top,root,nodes,fringe.size());
				return true;
			}
			fringe.pop();
			nodes++;

			if (top.depth < limit || !isDepthLimited) {

				std::vector<Move> moves = randomMoves ? grid.GetMovesShuffled() : grid.GetMoves();

				for (const Move& move : moves) {
					fringe.push({ top,move });
				}
			}

		}
		return false;
	}
};