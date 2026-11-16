#pragma once
#include "card.h"

typedef struct {
    Card cards[DECK_SIZE];
    int top;  //这个top代表当前排队的第一张牌，为一个索引
} Deck;

// 初始化牌堆
void initDeck(Deck* deck);

// 洗牌
void shuffleDeck(Deck* deck);

// 两数交换
void swap(Card* a, Card* b);

// 抽取一张牌，成功返回1，失败返回0
int drawCard(Deck* deck, Card* out);

// 获取剩余牌数
int getRemainingCards(const Deck* deck);

// 重置牌堆
void resetDeck(Deck* deck);

