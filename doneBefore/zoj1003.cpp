#include <stdio.h>
#include <math.h>
/*
#define kStateAWin				1
#define kStateBWin				2
#define kStateUnknow			3

// true -> smallNum wins;  false -> bigNum wins
*/
bool needtonamed(int startNum, int endNum, int bigNum, int smallNum);
bool check(int startN, int endN, int number);
bool check(int startN, int endN, int number, int smallNum);

int main()
{
/*	int primeNum_100[25] = 
	{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	int aSquareRoot = 0;
	int bSquareRoot = 0;
	int challengeResultState = kStateUnknow;*/
	int a = 0;
	int b = 0;
	int squareRoot = 0;
	int geaterNum = 0;
	int lessNum = 0;
	int challengeResult = 0;

	//----------------------Input-----------------------------
	while (scanf("%d %d", &a, &b) != EOF)
	{
	//--------------------Find-Winner-------------------------
		geaterNum = (a>b) ? a : b;
		lessNum = (a<b) ? a : b;
		if (geaterNum == lessNum || 1 ==lessNum)
		{
			challengeResult = geaterNum;
		} else
		{
			/*squareRoot = (int)sqrt(geaterNum);*/
			challengeResult = (needtonamed(2, 100, geaterNum, lessNum)) ? lessNum : geaterNum;
		}



	//----------------------Output----------------------------
		printf("%d\n", challengeResult);
	}

	return 0;
}

// true -> smallNum wins;  false -> bigNum wins
bool needtonamed(int startNum, int endNum, int bigNum, int smallNum)
{
	int startNumForSmall = startNum;
	int startNumForBig = startNum;
	int newSmall = 0;

	if (startNum >= endNum)
		return false;

	if (smallNum > 100)
	{
		while (0 != smallNum%startNumForSmall && startNumForSmall <= endNum && startNumForSmall <= 100)
			startNumForSmall++;
		/*The big number will win, when the small one can not be divide as it's a 100+number.*/
		if (startNumForSmall >= endNum || (smallNum/startNumForSmall == startNumForSmall) || startNumForSmall >= 100)
			return false;
		else 
			return needtonamed(startNumForSmall, endNum, bigNum, smallNum/startNum);
	}
	else
	{
		if (0 == bigNum%smallNum)
		{
			if (check(startNumForSmall, endNum, smallNum))
			{
				return false;
			}
			else
			{
				if (check(2, endNum, bigNum, smallNum))
					return false;
				else
					return true;
			}
		} else
		{
			if (check(2, endNum, bigNum, smallNum))
				return false;
			else
					return true;
		}
	}
}

bool check(int startN, int endN, int number)
{
	int i = 2;
	for ( i=startN; i<endN && i<100 && i != (int)sqrt(number); i++)
	{
		if (0 == number%i)
			return true;
	}
	return false;
}

bool check(int startN, int endN, int number, int smallNum)
{
	int i = 2;
	for ( i=startN; i<endN && i<100 && i != (int)sqrt(number); i++)
	{
		if (0 == number%i && number%smallNum != 0)
			return true;
	}
	return false;
}


// #include<iostream>
// using namespace std;
// int aa,bb;
// void dfs(int a,int b,int n)
// {
//     if(b==1)
//     {
//         if(a==1) aa=1;
//        bb=1;
//     }
//     if( n > 100 ||  aa==1 && bb==1  )
//         return;
//     if(b%n==0) dfs(a,b/n,n+1);
// 		if(a%n==0) dfs(a/n,b,n+1); 
//     dfs(a,b,n+1);
// }
// int main()
// {
//     int a,b,t;
//     while( cin >> a >> b )
//     {
//         if(a < b)
//         {t=a;a=b;b=t;}
//         aa=bb=0;
//        dfs(a,b,2);
//         if(aa==1)
//             cout << a;
//         else if(bb==1)
//             cout << b;
//         else
//            cout << a;
//        cout << endl;
//     }
//     return 0;
// }