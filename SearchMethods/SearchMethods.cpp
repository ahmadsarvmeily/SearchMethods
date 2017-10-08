#include "BlockGrid.h"
#include "BlockGridTester.h"

int main()
{
	// ----- Copy ctor test -----

	BlockGrid grid(4, 4, { {3,0},{3,1},{3,2} }, { {1,1},{2,1},{3,1} }, { 3,3 });
	{
		BlockGrid grid2 = grid;
		BlockGrid grid3(grid);

		grid2.MoveAgent(Move::Left);
		grid2.MoveAgent(Move::Left);
		grid3.MoveAgent(Move::Up);
		grid3.MoveAgent(Move::Up);
	}

	BlockGridTester tester(grid);
	tester.Run();

	// --------------------------

    return 0;
}