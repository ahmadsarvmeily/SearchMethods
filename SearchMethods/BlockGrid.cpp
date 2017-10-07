#include "BlockGrid.h"
#include <vector>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <cassert>

BlockGrid::BlockGrid(int gridWidth, int gridHeight, 
	std::initializer_list<BlockPos> initialTilePositions,
	std::initializer_list<BlockPos> goalTilePositions,
	BlockPos initialAgentPos) :
	gridWidth(gridWidth),
	gridHeight(gridHeight),
	currentTilePositions(initialTilePositions),
	goalTilePositions(goalTilePositions),
	nodes(gridWidth*gridHeight),
	agentNode(&(GetNode(initialAgentPos)))
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

void BlockGrid::MoveAgent(Move move)
{
	switch (move) {
	case Move::Left:
		if (agentNode->position.col > 0)
			ProcessAgentMove(*agentNode->left);
		break;
	case Move::Right:
		if (agentNode->position.col < gridWidth - 1)
			ProcessAgentMove(*agentNode->right);
		break;
	case Move::Up:
		if (agentNode->position.row > 0)
			ProcessAgentMove(*agentNode->up);
		break;
	case Move::Down:
		if (agentNode->position.row < gridHeight - 1)
			ProcessAgentMove(*agentNode->down);
	}
}

void BlockGrid::SetContents(Node & node, BlockContents contents) {
	node.contents = contents;
}

void BlockGrid::ProcessAgentMove(Node& moveToNode)
{
	if (moveToNode.contents == BlockContents::Tile) {
		int tileIndex = GetTileIndex(moveToNode);
		currentTilePositions[tileIndex] = agentNode->position;
	}
	SwapContents(*agentNode, moveToNode);
	agentNode = &moveToNode;
}

std::vector<Move> BlockGrid::GetMoves() const
{
	std::vector<Move> moves;

	if (agentNode->left != nullptr)
		moves.push_back(Move::Left);
	if (agentNode->right != nullptr)
		moves.push_back(Move::Right);
	if (agentNode->up != nullptr)
		moves.push_back(Move::Up);
	if (agentNode->down != nullptr)
		moves.push_back(Move::Down);

	return moves;
}

void BlockGrid::InitNodes()
{
	int index = 0;
	for (Node& node : nodes) {
		node.position = IndexToPos(index);
		index++;
	}

	for (Node& node : nodes) {
		int row = node.position.row;
		int col = node.position.col;

		if (col > 0) {
			node.left = &GetNode( BlockPos(row, col - 1) );
		}
		if (col < gridWidth - 1) {
			node.right = &GetNode( BlockPos(row, col + 1) );
		}
		if (row > 0) {
			node.up = &GetNode( BlockPos(row - 1, col) );
		}
		if (row < gridHeight - 1) {
			node.down = &GetNode( BlockPos(row + 1, col) );
		}
	}

	for (BlockPos& pos : currentTilePositions) {
		GetNode(pos).contents = BlockContents::Tile;
	}
	agentNode->contents = BlockContents::Agent;
}



BlockPos BlockGrid::IndexToPos(int index) const {
	return { index / gridWidth, index % gridWidth };
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

void BlockGrid::SwapContents(Node& node1, Node& node2) {
	BlockContents block1Contents = node1.contents;
	BlockContents block2Contents = node2.contents;

	SetContents(node1, block2Contents);
	SetContents(node2, block1Contents);
}
