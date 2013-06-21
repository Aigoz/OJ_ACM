#include <stdio.h>

long long calculateWays(int differenceValue);

long long waysTmp[50];
int main()
{
	int times, aInput, bInput;
	long long ways;
	scanf("%d", &times);
	while (times--)
	{
		scanf("%d %d", &aInput, &bInput);
		ways = calculateWays(bInput-aInput);
		printf("%lld\n",ways);
	}
	return 0;
}

long long calculateWays(int differenceValue)
{
	if (waysTmp[differenceValue])
		return waysTmp[differenceValue];
	else if(2 == differenceValue)
		waysTmp[2] = 2;
	else if (1 == differenceValue)
		waysTmp[1] = 1;
	else if (0 == differenceValue)
		waysTmp[0] = 1;
	else
		waysTmp[differenceValue] = 
		calculateWays(differenceValue-1)+calculateWays(differenceValue-2);
	return waysTmp[differenceValue];
}