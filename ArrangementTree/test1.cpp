#include "arrangementTree.h"

int main()
{
	int n = 5;
	int x[] = { 0,0,1,2,3,4,5,6,7,8,9 };
	int y[] = { '0','A','B','C','D','E' };
	
	backTrack(1, x, n);

	system("pause");
	return 0;
}