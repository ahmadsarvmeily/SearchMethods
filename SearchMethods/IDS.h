#pragma once
#include "BlockGrid.h"
#include "DFS.h"

class IDS {

public:
	static bool Search(const BlockGrid& root) {

		for (int i = 0; true; i++) {
			if (DFS::Search(root, i))
				return true;
		}
	}
};