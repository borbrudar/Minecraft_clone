#include "Tree.h"

void Tree::setTreeTop(int x, int y, int z)
{
	treeTop[0].x = x; treeTop[0].y = y + 1; treeTop[0].z = z;
	treeTop[1].x = x + 1; treeTop[1].y = y; treeTop[1].z = z;
	treeTop[2].x = x - 1; treeTop[2].y = y; treeTop[2].z = z;
	treeTop[3].x = x; treeTop[3].y = y; treeTop[3].z = z + 1;
	treeTop[4].x = x; treeTop[4].y = y; treeTop[4].z = z - 1;
}
