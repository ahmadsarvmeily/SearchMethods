#include "BlockGrid.h"
#include <iostream>
#include "DFS.h"
#include "BFS.h"
#include "IDS.h"
#include "AStar.h"
#include <chrono>

int main()
{	
	srand((unsigned int)time(NULL));
	const BlockGrid grid(4, 4, {{3,0},{3,1},{3,2}}, {{1,1},{2,1},{3,1}}, {3,3});
	
	constexpr int runs = 1;
	double sum = 0;

	for (int i = 0; i < runs; i++) {
		
		auto start = std::chrono::steady_clock::now();
		if (AStar::Search(grid)) {
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double, std::milli> duration = end - start;
			double elapsed = duration.count();
			std::cout << "time elapsed:\t" << elapsed << "ms" << std::endl << std::endl;
			sum += elapsed;
		}
		else {
			std::cout << "Error: Could not find solution" << std::endl;
			break;
		}

		double avg = sum / runs;
		std::cout << "Average time elapsed:\t" << avg << "ms" << std::endl;
	}
	

	return 0;
}