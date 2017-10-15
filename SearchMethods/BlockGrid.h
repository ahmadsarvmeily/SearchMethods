#pragma once
#include <vector>
#include <string>

class BlockPos {
public:
	BlockPos() = default;
	BlockPos(unsigned char row, unsigned char col) :
		row(row),
		col(col) {}

	BlockPos Left() {
		return BlockPos(row, col - 1);
	}
	BlockPos Right() {
		return BlockPos(row, col + 1);
	}
	BlockPos Up() {
		return BlockPos(row - 1, col);
	}
	BlockPos Down() {
		return BlockPos(row + 1, col);
	}

	int Distance(const BlockPos& pos) const {
		return std::abs(col - pos.col) +
			std::abs(row - pos.row);
	}

	bool operator==(const BlockPos& rhs) const {
		return (row == rhs.row && col == rhs.col);
	}
	bool operator!=(const BlockPos& rhs) const {
		return !(*this == rhs);
	}

	unsigned char row, col;
};

enum class BlockContents {
	Empty,
	Tile,
	Agent
};

enum class Move {
	Left,
	Right,
	Up,
	Down
};

/*
std::string MoveToStr(Move move) {
	switch (move) {
	case Move::Left:
		return "Left";
	case Move::Right:
		return "Right";
	case Move::Up:
		return "Up";
	case Move::Down:
		return "Down";
	}
}
*/

class BlockGrid {

public:
	BlockGrid(unsigned char gridWidth, unsigned char gridHeight,
		std::initializer_list<BlockPos> initialTilePositions,
		std::initializer_list<BlockPos> goalTilePositions,
		BlockPos initialAgentPos);

	bool IsInGoalState() const;
	void PrintState() const;
	int ManhattanDistances() const;
	BlockGrid& MoveAgent(Move move);
	std::vector<Move> GetMoves() const;
	std::vector<Move> GetMovesShuffled() const;

private:
	class Node {

	public:
		BlockPos position;
		BlockContents contents = BlockContents::Empty;
	};

	Node& GetNode(const BlockPos& pos) {
		return nodes[pos.col + pos.row*gridWidth];
	};

	void InitNodes();
	
	void ProcessAgentMove(const BlockPos moveToPos);
	int GetTileIndex(const Node& node) const;
	BlockPos IndexToPos(unsigned char index) const;
	
	unsigned char gridWidth, gridHeight;
	std::vector<BlockPos> currentTilePositions; 
	std::vector<BlockPos> goalTilePositions;
	std::vector<Node> nodes;
	BlockPos agentPos;
};