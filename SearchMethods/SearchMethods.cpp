#include "BlockGrid.h"
#include <iostream>
#include "DFS.h"
#include "BFS.h"
#include <chrono>

int main()
{	
	srand((unsigned int)time(NULL));
	const BlockGrid grid(4, 4, { {3,0},{3,1},{3,2} }, { {1,1},{2,1},{3,1} }, { 3,3 });

	constexpr int runs = 100;
	double sum = 0;
	for (int i = 1; i < runs+1; i++) {
		auto start = std::chrono::steady_clock::now();
		//BFS::Search(grid);
		DFS::Search(grid);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> duration = end - start;
		double elapsed = duration.count();
		std::cout << i << " | Time elapsed: " << elapsed << "ms" << std::endl;
		sum += elapsed;
	}
	double avg = sum / runs;
	std::cout << std::endl << "Average time elapsed: " << avg << "ms" << std::endl;

	return 0;
}