#pragma once
#include "BlockGrid.h"
#include <stack>
#include <iostream>
#include <memory>

class Node {

public:
	Node(BlockGrid grid, int depth) :
		grid(grid),
		depth(depth) {}

	Node(const Node& src, Move move) :
		grid(src.grid),
		parent(std::make_shared<Node>(src)),
		move(move),
		depth(src.depth + 1)
	{
		grid.MoveAgent(move);
	}

	BlockGrid grid;
	std::shared_ptr<Node> parent = nullptr;
	Move move;
	int depth;
};

std::stack<Node> CreatePath(const Node& goalNode) {
	std::stack<Node> path;
	path.push(goalNode);

	std::shared_ptr<Node> parent = goalNode.parent;
	while (parent->parent != nullptr) {
		path.push(*parent);
		parent = parent->parent;
	}

	return path;
}

void PrintMoves(std::stack<Node> path, bool printBoards) {
	while (!path.empty()) {
		Move move = path.top().move;

		switch (move) {
		case Move::Left:
			std::cout << "Left" << std::endl;
			break;
		case Move::Right:
			std::cout << "Right" << std::endl;
			break;
		case Move::Up:
			std::cout << "Up" << std::endl;
			break;
		case Move::Down:
			std::cout << "Down" << std::endl;
		}

		if (printBoards) {
			path.top().grid.PrintState();
		}
		path.pop();
	}
}

void PrintSolutionDetails(int depth, int expanded, size_t fringeSize) {
	std::cout << "depth:\t\t" << depth << std::endl;
	std::cout << "expanded:\t" << expanded << std::endl;
	std::cout << "fringe:\t\t" << fringeSize << std::endl;
}

void PrintDetails(const Node& solutionNode, const BlockGrid& root, int expanded, size_t fringeSize) {
	std::stack<Node> path = CreatePath(solutionNode);
	root.PrintState();
	PrintMoves(path, true);
	PrintSolutionDetails(solutionNode.depth, expanded, fringeSize);
}