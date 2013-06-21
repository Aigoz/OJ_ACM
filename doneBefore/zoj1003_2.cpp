#include <stdio.h>
#include <math.h>

#define kStateDivideTrue		1
#define kStateDivideFalse		2
#define kStateDivideNeedMore	3

void resetKeyNumArray(int keyNum[]);
int canBeDivided(int beDividedNum, int startNum, int keyNum[]);

int main() 
{
	int aInput,bInput;
	int bigger,smaller;
	int challengeResult;
	int keyNum[100] ={0};
	int state = 0;

		//----------------------Input-----------------------------
	while (scanf("%d %d", &aInput, &bInput) != EOF)
	{
		//--------------------Find-Winner-------------------------
		bigger = (aInput>bInput) ? aInput : bInput;
		smaller = (aInput<bInput) ? aInput : bInput;
		challengeResult = bigger;

		if (bigger<=100 && smaller<=100)
		{
			challengeResult = bigger;
		} 
		else if (bigger>100 && smaller<=100)
		{
			if (0 != bigger%smaller)
			{
				keyNum[0] = smaller;
				state = canBeDivided(bigger, 2, keyNum);
				if (kStateDivideTrue == state)
					challengeResult = bigger;
				else
					challengeResult = smaller;
			}
			else
			{
				resetKeyNumArray(keyNum);
				state = canBeDivided(smaller, 2, NULL);
				if (kStateDivideTrue == state)
				{
					challengeResult = bigger;
				}
				else
				{
					resetKeyNumArray(keyNum);
					keyNum[0] = smaller;
					state = canBeDivided(bigger, 2, keyNum);
					if (kStateDivideTrue == state)
						challengeResult = bigger;
					else
						challengeResult = smaller;
				}
			}
		} 
		else if (bigger>100 && smaller>100)
		{
			resetKeyNumArray(keyNum);
			state = canBeDivided(smaller, 2, keyNum);
			if (kStateDivideTrue == state)
			{
				state = canBeDivided(bigger, 2, keyNum);
				if (kStateDivideTrue == state)
				{
					challengeResult = bigger;
				}
				else if (kStateDivideFalse == state)
				{
					challengeResult = smaller;
				}
				else
				{
					state = canBeDivided(smaller, 2, keyNum);
					if (kStateDivideTrue == state)
					{
						challengeResult = bigger;
					}
					else
						challengeResult = smaller;
				}
			}
			else
				challengeResult = bigger;
		}
		else
		{
			challengeResult = bigger;
		}

		//----------------------Output----------------------------
		printf("%d\n", challengeResult);
		resetKeyNumArray(keyNum);
		state = 0;
	}
	return 0;
}

void resetKeyNumArray(int keyNum[])
{
	int i = 0;
	for (i=0; i<100 && keyNum[i]!=0; i++)
	{
		keyNum[i] = 0;
	}
}

int canBeDivided(int beDividedNum, int startNum, int keyNum[])
{
	int state = 0;
	int i = 0;
	int conflict = 0;
	if(startNum >= beDividedNum || startNum >= 100)
		return kStateDivideFalse;
	else if (1 == beDividedNum)
	{
		return kStateDivideFalse;
	}
	else
	{
		if (0 == beDividedNum%startNum && beDividedNum/startNum	<=100)
		{
			if(NULL == keyNum)
				return kStateDivideTrue;
			else if (beDividedNum/startNum == startNum)
			{
				return canBeDivided(beDividedNum, startNum+1,keyNum);
			}
			else
			{
				for (i=0; i<100 && keyNum[i] !=0; i++)
				{
					// 0:no conflict  1:has conflict
					conflict = (keyNum[i] == startNum || keyNum[i] == beDividedNum/startNum) ? 1 : 0;
					break;
				}
				if (0 == conflict)
				{
					i = 0;
					while (keyNum[i] !=0)
						i++;
					keyNum[i] = startNum;
					keyNum[i+1] = beDividedNum/startNum;
					return kStateDivideTrue;
				}
				else if (1 == conflict)
				{
					state = canBeDivided(beDividedNum, startNum+1, keyNum);
					if (kStateDivideTrue == state)
					{
						return kStateDivideTrue;
					}
					else
					{
						return kStateDivideNeedMore;
					}
				}
				else 
					return kStateDivideTrue;
			}
		}
		else
		{
			return canBeDivided(beDividedNum, startNum+1, keyNum);
		}
	}
}