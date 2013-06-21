// 我这里只记录了一次power值，但是我觉得应该要不停的刷新power，而且power值不能算上别人的已放的射击范围。
// 为了要硬用上链表，我的逻辑乱了很多，中间过程也冗余了很多。
// 其实用数组完全够了,而且很简单。
// 中间关于删除中间项，其实可以用双向链表，循环次数会减少。

//////////////////////////////////////////////////////////////////////////
//单独设置一个头结点 和 未单独设置一个头结点是有区别的！！！！
//单独设置头结点 可以用在void 函数中 用 *head->???来更新
//而未单独设置头结点的 需要改变head地址，所以要不在void中传**  要不就在返回值返回新head
//////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>

#define kSquareStateWall			1
#define kSquareStateCastle			2
#define kSquareStateUnderFire		3
#define kSquareStateEmpty			4

struct squareLeft_node {
	int row;
	int column;
	int power;
	struct squareLeft_node *next;
};

struct squareLeft_node *createSquareLeft(int city[4][4], int size);
struct squareLeft_node *pickTheWeakestNode(struct squareLeft_node *leftS);
int getNodePower(int row, int column, int city[4][4], int size);
struct squareLeft_node *updateCityStateAndSquareLeftByWeakestNode(struct squareLeft_node *weakest, int city[4][4], struct squareLeft_node *leftS, int size);
void resetCityState(int city[4][4]);

// private
struct squareLeft_node *deleteNode(struct squareLeft_node *head, int row, int column);

int main()
{
	int sizeOfCity = 0;	
	char squareType;
	int cityState[4][4] = {0};
	int row,column;
	int maxBlockhouse = 0;

	struct squareLeft_node *squareLeftHead;
	struct squareLeft_node *weakestNode;

	while (scanf("%d", &sizeOfCity) != EOF)
	{
		if (0 == sizeOfCity)
			return 0;
		//----------------------Input-----------------------------
		getchar();
		for (row = 0; row < sizeOfCity; ++row)
		{
			for (column=0; column < sizeOfCity; ++column)
			{
				scanf("%c", &squareType);
				if ('.' == squareType)
				{
					cityState[row][column] = kSquareStateEmpty;
				} else if ('X' == squareType)
				{
					cityState[row][column] = kSquareStateWall;
				}
			}
			getchar();
		}

		//---------------------Find max------------------------
		squareLeftHead = createSquareLeft(cityState, sizeOfCity);
		weakestNode = squareLeftHead;

		while (NULL != squareLeftHead)
		{
			weakestNode = pickTheWeakestNode(squareLeftHead);
			squareLeftHead = updateCityStateAndSquareLeftByWeakestNode(weakestNode, cityState, squareLeftHead, sizeOfCity);
			maxBlockhouse++;
		}


		//----------------------Output--------------------------
		printf("%d\n", maxBlockhouse);

		//---------------------ResetCity-------------------------
		resetCityState(cityState);
		maxBlockhouse = 0;
		sizeOfCity = 0;
	}
	return 0;
}


struct squareLeft_node *createSquareLeft(int city[4][4], int size)
{
	struct squareLeft_node *head, *tail, *tmp;
	int row,column;

	head = tail = NULL;
	if (0 == city[0][0])
	{
		return NULL;
	}

	for (row = 0; row < size; ++row)
	{
		for (column = 0; column < size; ++column)
		{
			if (0 == city[row][column])
			{
				row = 4;
				column = 4;
				return head;
			}
			if ( (kSquareStateWall == city[row][column]) || 
				(kSquareStateUnderFire == city[row][column]) || 
				(kSquareStateCastle == city[row][column]) )
			{
				continue;
			}
			tmp = (struct squareLeft_node*)malloc(sizeof(struct squareLeft_node));
			tmp->column = column;
			tmp->row = row;
			tmp->power = getNodePower(row, column, city, size);
			tmp->next = NULL;

			if (NULL == head)
			{
				// For the first time 
				head = tmp;
			} else	
			{
				// Insert the new node
				tail->next = tmp;
			}
			// update tail
			tail = tmp;
		}
	}

	return head;
}

struct squareLeft_node *pickTheWeakestNode(struct squareLeft_node *leftS)
{
	struct squareLeft_node *weakest, *tmp;
	weakest = leftS;
	tmp = leftS;

	while (tmp != NULL)
	{
		if (weakest->power > tmp->power)
		{
			weakest = tmp;
		}
		tmp = tmp->next;
	}
	return weakest;
}

int getNodePower(int row, int column, int city[4][4], int size)
{
	int power = 0;
	int r,c;

	// power upward
	if (0 != row)
	{
		for (r = row-1; r >= 0; --r)
		{
			if (kSquareStateWall != city[r][column])
				power++;
			else
				break;
		}
	}
	// power downward
	if (size != row)
	{
		for (r = row+1; r < size; ++r)
		{
			if (kSquareStateWall != city[r][column])
				power++;
			else
				break;
		}
	}
	// power leftward
	if (0 != column)
	{
		for (c = column-1; c >= 0; --c)
		{
			if (kSquareStateWall != city[row][c])
				power++;
			else
				break;
		}
	}
	// power rightward
	if (size != column)
	{
		for (c = column+1; c < size; ++c)
		{
			if (kSquareStateWall != city[row][c])
				power++;
			else
				break;
		}
	}

	return power;
}

struct squareLeft_node *updateCityStateAndSquareLeftByWeakestNode(struct squareLeft_node *weakest, int city[4][4], struct squareLeft_node *leftS, int size)
{
	int row = weakest->row;
	int column = weakest->column;
	struct squareLeft_node *newHead = leftS;
	int r,c;

	// power upward
	if (0 != row)
	{
		for (r = row-1; r >= 0; --r)
		{
			if (kSquareStateWall != city[r][column])
			{
				city[r][column] = kSquareStateUnderFire;
				leftS = deleteNode(leftS, r, column);
			}
			else
				break;
		}
	}
	// power downward
	if (size != row)
	{
		for (r = row+1; r < size; ++r)
		{
			if (kSquareStateWall != city[r][column])
			{
				city[r][column] = kSquareStateUnderFire;
				leftS = deleteNode(leftS, r, column);
			}
			else
				break;
		}
	}
	// power leftward
	if (0 != column)
	{
		for (c = column-1; c >= 0; --c)
		{
			if (kSquareStateWall != city[row][c])
			{
				city[row][c] = kSquareStateUnderFire;
				leftS = deleteNode(leftS, row, c);
			}
			else
				break;
		}
	}
	// power rightward
	if (size != column)
	{
		for (c = column+1; c < size; ++c)
		{
			if (kSquareStateWall != city[row][c])
			{
				city[row][c] = kSquareStateUnderFire;
				leftS = deleteNode(leftS, row, c);
			}
			else
				break;
		}
	}
	city[row][column] = kSquareStateCastle;
	newHead = deleteNode(leftS, row, column);

	return newHead;
}

void resetCityState(int city[4][4])
{
	int i,j;
	for (i = 0; i<4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			city[i][j] = 0;
		}
	}
}

struct squareLeft_node *deleteNode(struct squareLeft_node *head, int row, int column)
{
	struct squareLeft_node *tmp = head;
	struct squareLeft_node *preNode = NULL;

	preNode = tmp;
	while (NULL != tmp)
	{
		if ( (tmp->row == row) && (tmp->column == column))
		{
			break;
		}
		preNode = tmp;
		tmp = tmp->next;
	}

	if (NULL == tmp)
	{
		return head;
	}

	if (head == tmp)
	{
		head = tmp->next;
		free(tmp);
	} else
	{
		preNode->next = tmp->next;
		free(tmp);
	}

	return head;
}