#pragma once
#include"player.h"
#include"hand.h"
#include"deck.h"

#define MAX_PLAYERS 6
#define MIN_PLAYERS 2

typedef enum {
	GAME_UNSET = 0,
	GAME_SINGLE_PLAYER,
	GAME_MULTIPLAYER,
	GAME_HUMAN_VS_COMPUTER
}GameMode;//定义游戏模式

typedef struct {
	GameMode mode;
	Player player[MAX_PLAYERS];//构建玩家数组
	int playerCount;//确定参与游戏的玩家人数
}Game;//定义游戏

//-----------------------------游戏初始化------------------------------//

//初始化整个游戏,并初始化玩家的手牌
void initGame(Game* game);

//设置游戏模式,成功设置返回1
int setGameMode(Game* game,GameMode mode);

//确定玩家人数,成功设置返回1
int setPlayerCount(Game* game, int count);

//配置所有玩家的姓名,成功设置返回1
int configureAllplayers(Game* game);


//------------------------------游戏开始-------------------------------//

//给所有玩家发牌，成功发牌返回1
int dealCards(Game* game, Deck* deck);

//清空玩家手牌，保持玩家战绩与玩家信息
void resetGameRounds(Game* game);

//开启新的一轮游戏
int startNewRound(Game* game, Deck* deck);

//更新玩家获奖信息（获胜者，获胜的次数）
void updateStatistics(Game* game, const int winners[], int winnerCount);




//-------------------------------游戏清理-----------------------------//

//清空整个游戏
void clearGame(Game* game);