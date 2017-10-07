#pragma once
#include <vector>

class BlockPos {
public:
	BlockPos() = default;
	BlockPos(int row, int col) :
		row(row),
		col(col) {}

	bool operator==(const BlockPos& rhs) const {
		return (row == rhs.row && col == rhs.col);
	}
	bool operator!=(const BlockPos& rhs) const {
		return !(*this == rhs);
	}

	int row, col;
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

class BlockGrid {

public:
	BlockGrid(int gridWidth, int gridHeight,
		std::initializer_list<BlockPos> initialTilePositions,
		std::initializer_list<BlockPos> goalTilePositions,
		BlockPos initialAgentPos);

	bool IsInGoalState() const;
	void PrintState() const;
	void MoveAgent(Move move);
	std::vector<Move> GetMoves() const;

private:
	class Node {

	public:
		BlockPos position;
		BlockContents contents = BlockContents::Empty;
		Node* left = nullptr;
		Node* right = nullptr;
		Node* up = nullptr;
		Node* down = nullptr;
	};

	Node& GetNode(BlockPos& pos) {
		return nodes[pos.col + pos.row*gridWidth];
	};

	void InitNodes();
	void SetContents(Node& node, BlockContents contents);
	void SwapContents(Node& node1, Node& node2);
	void ProcessAgentMove(Node& moveToNode);
	int GetTileIndex(const Node& node) const;
	BlockPos IndexToPos(int index) const;
	
	const int gridWidth, gridHeight;
	std::vector<BlockPos> currentTilePositions;
	const std::vector<BlockPos> goalTilePositions;
	std::vector<Node> nodes;
	Node* agentNode;
};