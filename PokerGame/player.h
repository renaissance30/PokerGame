#pragma once
#include"hand.h"
#include"card.h"

#define MAX_PLAYERS 6
#define MIN_PLAYERS 2
#define NAME_LENGTH 32

typedef struct {
	char name[NAME_LENGTH];
	Hand hand;

    // 累计战绩
    int roundsPlayed;       // 参与局数
    int wins;   //获胜局数
}Player;

//初始化用户信息
void initPlayer(Player* player);

//修改玩家信息,成功修改返回1，失败则返回0
int setPlayername(Player* player,const char*name);

//玩家接收牌
int receiveCard(Player* player, Card card);

//清空玩家的手牌
void clearPlayercard(Player* player);


