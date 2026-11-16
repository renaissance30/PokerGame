#pragma once

#include"evaluate.h"

/* 

 * 比较两手牌的大小。
 *
 * @param a 第一手牌的 HandValue
 * @param b 第二手牌的 HandValue
 * @return 1: a > b
 *        -1: a < b
 *         0: a == b
 
 */


int compareHands( Result a,  Result b);


//找到胜者
int findWinners(const Result values[], int playerCount, int winners[]);