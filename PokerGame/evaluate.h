#pragma once
#include"hand.h"

typedef enum
{
	HIGH_CARD = 0,   //高牌
	ONE_PAIR,        //一对
	TWO_PAIR,        //两对
	THREE,           //三条
	STRAIGHT,        //顺子
	FLUSH,           //同花
	FULL_HOUSE,      //三拖二
	FOUR,            //四炸
	STRAIGHT_FLUSH,  //同花顺
	ROYAL_FLUSH,     //皇家同花顺
}card_kind;

typedef struct
{
	card_kind HandRank;   //牌型
	int value[5];        //具体序列分析
}Result;

Result FirstCompare(Card* arr);  //单个人手牌分析
