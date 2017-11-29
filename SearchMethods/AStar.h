#pragma once
#include "BlockGrid.h"
#include "TreeSearch.h"
#include <queue>
#include <iostream>
#include <memory>

class AStar {

public:
	static bool Search(const BlockGrid& root) {

		int nodes = 0;

		std::priority_queue<AStarNode, std::vector<AStarNode>, LowestF> fringe;

		fringe.push({ root,0 });

		while (!fringe.empty()) {
			
			const AStarNode minFNode = fringe.top();

			if (minFNode.grid.IsInGoalState()) {
				PrintDetails(minFNode, root, nodes, fringe.size());
				return true;
			}
			else {
				const auto& moves = minFNode.grid.GetMoves();
				fringe.pop();
				nodes++;
				for (const Move& move : moves) {
					fringe.push({ minFNode,move });
				}
			}
		}
		return false;
	}

private:
	class AStarNode : public Node {

	public:
		AStarNode(BlockGrid grid, int depth) :
			Node(grid,depth),
			f(F())
		{}

		AStarNode(const AStarNode& src, Move move) :
			Node(src, move),
			f(F())
		{}

		int f;

	private:
		int F() const {
			return G(depth) + H(grid);
		}
		int G(int depth) const {
			return depth;
		}
		int H(const BlockGrid& grid) const {
			return grid.ManhattanDistances();
		}
	};

	struct LowestF {

		bool operator()(const AStarNode& lhs, const AStarNode& rhs) const {
			return lhs.f > rhs.f;
		}
	};
};