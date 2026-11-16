#pragma once
#include"card.h"
#include"hand.h"
#include<stddef.h>
#include"evaluate.h"
#include"player.h"
#define UI_WIDTH 60

/* ==================== 输入函数 ==================== */

/**
 * 获取指定范围内的整数。
 * @param prompt 提示信息
 * @param min 最小允许值
 * @param max 最大允许值
 * @param outValue将用户输入的参量通过指针的形式传出去
 * @return 对于EOF返回0，正常输入返回1
 */
int getIntInput(const char* prompt, int min, int max,int* outValue);

/**
 * 获取字符串输入。
 * @param prompt 提示信息
 * @param buffer 用于存储输入的字符数组
 * @param size 缓冲区大小
 * @return 对于EOF输入返回0.正常输入返回1
 */
int getStringInput(const char* prompt, char* buffer, size_t size);


/* ==================== 输出函数 ==================== */

/**获取字符串长度函数。 */
int getDisplayWidth(const char* str);

/**将字符串居中。 */
void printCentered(const char* str);

/** 输出游戏欢迎界面。 */
void printWelcome(void);

/** 输出游戏模式选择菜单。 */
void printMenu(void);

/** 输出一张扑克牌。 */
void printCard(const Card* card);

/** 输出玩家的五张手牌。 */
void printHand(const Hand* hand);

/**输出玩家的当前牌型。 */
void printHandRank(const Result* result);

/**输出玩家的历史战绩。*/
void printPlayerStats(const Player* player);

/**打印宽为六十的分割。 */
void printLine(void);