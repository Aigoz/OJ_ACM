/***************************************
*	   可以把问题看成2×n个方格是由 竖着的1个方块+2×(n-1)方格 和 2个横着的方块+2*(n-2)方格 组成
****************************************/
#include <stdio.h>

__int64 nameIt(int n);
__int64 tmpArray[51];

int main()
{
	int num;
	while (scanf("%d", &num) != EOF)
	{
		printf("%I64d\n", nameIt(num));
	}
	return 0;
}

__int64 nameIt(int n)
{
	if (tmpArray[n])
		return tmpArray[n];
	else if (1 == n)
		tmpArray[n] = 1;
	else if (2 == n)
		tmpArray[n] = 2;
	else
		tmpArray[n] = nameIt(n-1) + nameIt(n-2);
	return tmpArray[n];
}