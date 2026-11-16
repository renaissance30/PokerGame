#include"compare.h"
#include"player.h"
#include<stdio.h>

//比较两个人的手牌
//return值说明： 1:A胜  -1:B胜  0:平局
int compareHands(Result a, Result b)
{
	//比较牌型 
	if (a.HandRank > b.HandRank)
	{
		return 1;
	}
	if (a.HandRank < b.HandRank)
	{
		return -1;
	}

	//---------------------------------------------------------------------------------
	 //比较序列
	for (int i = 0; i < 5; i++)
	{
		if (a.value[i] > b.value[i])
			return 1;
		if (a.value[i] < b.value[i])
			return -1;
	}


	return 0;
}


int findWinners(const Result value[], int playerCount, int winners[]) {
	
	if (value == NULL || winners == NULL ||
		playerCount <= 0 || playerCount > MAX_PLAYERS) {
		return 0;
	}
	
	
	// 初始化第一个玩家为赢家
	int maxIndex = 0;
	winners[0] = 0;
	int winnerCount = 1;

	// 从第二个玩家开始遍历
	for (int i = 1; i < playerCount; i++) {

		int result = compareHands(value[i], value[maxIndex]);

		if (result > 0) {
			// 找到更大的牌
			maxIndex = i;
			winnerCount = 0;
			winners[winnerCount++] = i;
		}
		else if (result == 0) {
			// 找到并列赢家
			winners[winnerCount++] = i;
		}
	}

	return winnerCount;
}