#pragma once
#include "BlockGrid.h"
#include <queue>
#include <iostream>
#include <vector>

class AStar {

public:
	static bool Search(const BlockGrid& root) {

		if (root.IsInGoalState()) return true;

		std::priority_queue<Node, std::vector<Node>, LowestF> fringe;
		fringe.push({ root,0 });

		while (!fringe.empty()) {
			
			const Node& minFNode = fringe.top();

			if (minFNode.grid.IsInGoalState()) {
				std::cout << minFNode.depth << std::endl;
				return true;
			}
			else {
				const auto& moves = minFNode.grid.GetMoves();
				for (const Move& move : moves) {
					Node node = fringe.top();
					node.grid.MoveAgent(move);
					node.depth++;
					node.RecalculateF();
					fringe.push(std::move(node));
				}
				fringe.pop();
			}
		}
		return false;
	}

private:
	class Node {

	public:
		Node(BlockGrid grid, int depth) :
			grid(grid),
			depth(depth),
			f(CalculateF()) {}

		BlockGrid grid;
		int depth;
		int f;

		void RecalculateF() {
			f = CalculateF();
		}

	private:
		inline int CalculateF() const {
			return G(depth) + H(grid);
		}
		inline int G(int depth) const {
			return depth;
		}
		inline int H(const BlockGrid& grid) const {
			return grid.ManhattanDistances();
		}
	};

	struct LowestF
	{
		bool operator()(const Node& lhs, const Node& rhs) const
		{
			return lhs.f > rhs.f;
		}
	};
};