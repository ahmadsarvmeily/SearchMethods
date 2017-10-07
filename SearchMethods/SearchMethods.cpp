#include "BlockGrid.h"
#include "BlockGridTester.h"

int main()
{
	BlockGrid grid(4, 4, { {3,0},{3,1},{3,2} }, { {1,1},{2,1},{3,1} }, {3,3});

	BlockGridTester tester(grid);
	tester.Run();

    return 0;
}