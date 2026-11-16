#pragma once

#define HAND_SIZE 5
#include"card.h"


typedef struct {
	Card cards[HAND_SIZE];
	int count;//这里的count可以作为发牌时发到哪的指标
}Hand;

//初始化玩家的手牌，并将count赋初值0
void initHand(Hand* hand);

//给玩家分发手牌，分发失败返回0，成功返回1
int addCard(Hand* hand,Card card);

//给玩家的手牌排序(bubbleSort)
void sortHand(Hand* hand);