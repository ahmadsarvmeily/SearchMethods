#include "BlockGrid.h"
#include <vector>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <cassert>
#include <algorithm>

BlockGrid::BlockGrid(unsigned char gridWidth, unsigned char gridHeight,
	std::initializer_list<BlockPos> initialTilePositions,
	std::initializer_list<BlockPos> goalTilePositions,
	BlockPos initialAgentPos) :
	gridWidth(gridWidth),
	gridHeight(gridHeight),
	currentTilePositions(initialTilePositions),
	goalTilePositions(goalTilePositions),
	nodes(gridWidth*gridHeight),
	agentPos(initialAgentPos)
{
	assert(currentTilePositions.size() == this->goalTilePositions.size());
	InitNodes();
}

bool BlockGrid::IsInGoalState() const {
	
	for (unsigned int i = 0; i < goalTilePositions.size(); i++) {
		if (goalTilePositions[i] != currentTilePositions[i]) {
			return false;
		}
	}
	return true;
}

void BlockGrid::PrintState() const
{
	std::cout << std::endl;
	for (unsigned int i = 0; i < nodes.size(); i++) {

		BlockPos pos = IndexToPos(i);

		if(pos.col == 0)
			std::cout << "\t";

		const Node& node = nodes.at(i);

		switch (node.contents) {
		case BlockContents::Empty:
			std::cout << "[ ]";
			break;

		case BlockContents::Tile: {
			int tileIndex = GetTileIndex(node);
			std::cout << "[" << tileIndex << "]";
			}
			break;

		case BlockContents::Agent:
			std::cout << "[A]";
			break;
		}

		if (pos.col == gridWidth - 1)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

BlockGrid& BlockGrid::MoveAgent(Move move)
{
	switch (move) {
	case Move::Left:
		if (agentPos.col > 0)
			ProcessAgentMove(agentPos.Left());
		break;
	case Move::Right:
		if (agentPos.col < gridWidth - 1)
			ProcessAgentMove(agentPos.Right());
		break;
	case Move::Up:
		if (agentPos.row > 0)
			ProcessAgentMove(agentPos.Up());
		break;
	case Move::Down:
		if (agentPos.row < gridHeight - 1)
			ProcessAgentMove(agentPos.Down());
	}
	return *this;
}

void BlockGrid::ProcessAgentMove(const BlockPos moveToPos)
{
	Node& moveToNode = GetNode(moveToPos);
	Node& agentNode = GetNode(agentPos);
	if (moveToNode.contents == BlockContents::Tile) {
		int tileIndex = GetTileIndex(moveToNode);
		currentTilePositions[tileIndex] = agentPos;
	}
	agentNode.SwapContents(moveToNode);
	agentPos = moveToNode.position;
}

std::vector<Move> BlockGrid::GetMoves() const
{
	std::vector<Move> moves;

	if (agentPos.col > 0)
		moves.emplace_back(Move::Left);
	if (agentPos.col < gridWidth - 1)
		moves.emplace_back(Move::Right);
	if (agentPos.row > 0)
		moves.emplace_back(Move::Up);
	if (agentPos.row < gridHeight - 1)
		moves.emplace_back(Move::Down);

	return moves;
}

std::vector<Move> BlockGrid::GetMovesShuffled() const
{
	std::vector<Move> shuffledMoves = GetMoves();
	std::random_shuffle(shuffledMoves.begin(), shuffledMoves.end());
	return shuffledMoves;
}

void BlockGrid::InitNodes()
{
	int index = 0;
	for (Node& node : nodes) {
		node.position = IndexToPos(index);
		index++;
	}

	for (BlockPos& pos : currentTilePositions) {
		GetNode(pos).contents = BlockContents::Tile;
	}
	GetNode(agentPos).contents = BlockContents::Agent;
}

BlockPos BlockGrid::IndexToPos(unsigned char index) const {
	return BlockPos( index / gridWidth, index % gridWidth );
}

int BlockGrid::GetTileIndex(const Node& node) const
{
	int tileIndex = 0;
	for (const BlockPos& pos : currentTilePositions) {
		if (node.position == pos) {
			return tileIndex;
		}
		tileIndex++;
	}
	return -1;
}