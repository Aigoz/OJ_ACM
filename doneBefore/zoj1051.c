#include <stdio.h>
#include <string.h>

int calculateSumK(int squareRow, int squareColumn, int squareBef[][20]);
int squareUpdate(int squareBef[][20], int kArray[][20], int day, int dk[]);

int main()
{
	int inputBlockNumber = 0;				// Input Formate: the number you will input
	int days = 0;
	int square[20][20] = {0};
	int dk[16] = {0};				// input dk16
	int kArray[20][20] = {0};		// temp kSumArray

	int row = 0;
	int column = 0;

	int tmpN = 0;

	scanf("%d", &inputBlockNumber);
	while (inputBlockNumber--)
	{
	// ---------------Input Formate-----------------------
		//input days:
		scanf("%d", &days);
		//input dk[]:
		for (tmpN=0; tmpN<16; tmpN++)
		{
			scanf("%d", &dk[tmpN]);
		}
		//input square:
		for (row=0; row < 20; row++)
		{
			for (column=0; column < 20; column++)
			{
				scanf("%d", &square[row][column]);
			}
		}

	// ------------------Calculate------------------------
		while (days--)
		{
			//sumK for each point
			// No.1 the first method
			for (row=0; row < 20; row++)
			{
				for (column=0; column < 20; column++)
				{
					kArray[row][column] = calculateSumK(row, column, square);
				}
			}
			
			//Update Square by kArray[][]
			if (squareUpdate(square, kArray, days, dk))
			{
				printf("squareUpdate error");
			}
		}

	// ---------------Output Formate-----------------------
		for (row=0; row < 20; row++)
		{
			for (column=0; column < 20; column++)
			{
				printf("%c", square[row][column]);
			}
			printf("\n");
		}
	}

	if (inputBlockNumber != 0)
	{
		printf("\n");
	}

	return 0;
}


int calculateSumK(int squareRow, int squareColumn, int squareBef[][20])
{
	int sumK = 0;
	
	sumK += squareBef[squareRow][squareColumn];
	if (squareRow != 0)
	{
		sumK += squareBef[squareRow-1][squareColumn];
	}
	if (squareRow != 19)
	{
		sumK += squareBef[squareRow+1][squareColumn];
	}
	if (squareColumn != 0)
	{
		sumK += squareBef[squareRow][squareColumn-1];
	}
	if (squareColumn != 19)
	{
		sumK += squareBef[squareRow][squareColumn+1];
	}
	
	return sumK;
}

int squareUpdate(int squareBef[][20], int kArray[][20], int day, int dk[])
{
	int row = 0;
	int column = 0;
	if (0 != day)
	{
		for (row=0; row < 20; row++)
		{
			for (column=0; column < 20; column++)
			{
				squareBef[row][column] += dk[(kArray[row][column])];
				squareBef[row][column] = 
					(squareBef[row][column] >= 0) ? squareBef[row][column] : 0;
				squareBef[row][column] = 
					(squareBef[row][column] <= 3) ? squareBef[row][column] : 3;
			}
		}
	}
	else
	{
		for (row=0; row < 20; row++)
		{
			for (column=0; column < 20; column++)
			{
				for (column=0; column < 20; column++)
				{
					squareBef[row][column] += dk[(kArray[row][column])];
					squareBef[row][column] = 
						(squareBef[row][column] >= 0) ? squareBef[row][column] : 0;
					squareBef[row][column] = 
						(squareBef[row][column] <= 3) ? squareBef[row][column] : 3;
					
					switch(squareBef[row][column])
					{
					case 0:
						squareBef[row][column] = '.';
						break;
					case 1:
						squareBef[row][column] = '!';
						break;
					case 2:
						squareBef[row][column] = 'X';
						break;
					case 3:
						squareBef[row][column] = '#';
						break;
					default:
						squareBef[row][column] = '.';
						break;
					}
				}

			}
		}
	}
	return 0;
}


