#include "card.h"
#include "deck.h"
#include "hand.h"
#include "game.h"
#include "player.h"
#include "compare.h"
#include "evaluate.h"
#include "io.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);//支持中文输入输出

	srand((unsigned int)time(NULL));
	Game game;
	Deck deck;
	Result result[MAX_PLAYERS];

	initGame(&game);

	printWelcome();

	while (1) {    //这个死循环的目的是为了防止用户玩了一次游戏就被迫退出了
		printMenu();

		int choice;

		if (!getIntInput("请选择游戏模式：", 1, 4, &choice)) {
			break;
		}
		if (choice == 4) {
			break;
		}
		
		GameMode mode;

		switch (choice) {
		case 1:
			mode = GAME_SINGLE_PLAYER;
			break;
		case 2:
			mode = GAME_MULTIPLAYER;
			break;
		case 3:
			mode = GAME_HUMAN_VS_COMPUTER;
			break;
		default:
			continue;
		}

		if (!setGameMode(&game, mode)) {
			continue;
		}

		if (game.mode == GAME_SINGLE_PLAYER) {
			if (!setPlayerCount(&game, 1) || !configureAllplayers(&game)) {
				clearGame(&game);
				continue;
			}
		}
		else if (game.mode == GAME_HUMAN_VS_COMPUTER) {
			if (!setPlayerCount(&game, 2)) {
				clearGame(&game);
				continue;
			}
			char name[NAME_LENGTH];
			printf("请输入您的姓名（直接回车使用默认名字）：");
			if (fgets(name, sizeof name, stdin) == NULL) {
				clearGame(&game);
				continue;
			}
			name[strcspn(name, "\n")] = '\0';
			if (name[0] == '\0') {
				snprintf(name, sizeof name, "玩家");
			}
			if (!setPlayername(&game.player[0], name) || !setPlayername(&game.player[1], "computer")) {
				clearGame(&game);
				continue;
			}
		}
		else if (game.mode == GAME_MULTIPLAYER) {
			int count;

			if (!getIntInput("请输入玩家人数（2-6）：", MIN_PLAYERS, MAX_PLAYERS, &count)) {
				clearGame(&game);
				continue;
			}
			if (!setPlayerCount(&game, count) || !configureAllplayers(&game)) {
				clearGame(&game);
				continue;
			}
		}

		//开始游戏
		while (1) {
			if (!startNewRound(&game, &deck)){
				printf("发牌失败！\n");
				break;
			}
			for (int i = 0;i < game.playerCount;i++) {
				printHand(&game.player[i].hand);
				printf("\n");

				result[i] = FirstCompare(game.player[i].hand.cards);

				printf("%s的牌面为", game.player[i].name);
				printHandRank(&result[i]);
				printf("\n");
			}
			if (game.mode == GAME_SINGLE_PLAYER) {

				// 单人模式：只记录练习场数，不计算胜负
				game.player[0].roundsPlayed++;

				printf("\n单人练习模式：本局牌型已分析完成！\n");

			}
			else {
				int winners[MAX_PLAYERS];

				int winnerCount = findWinners(result, game.playerCount, winners);

				if (winnerCount > 0) {
					updateStatistics(&game, winners, winnerCount);
					printf("\n本局的胜者是：\n");
					for (int i = 0;i < winnerCount;i++) {
						int index = winners[i];
						printf("%s   ", game.player[index].name);
					}

				}
				else {
					printf("胜者数据获取失败！\n");
					break;
				}
				printf("\n========== 当前战绩 ==========\n");

				for (int i = 0;i < game.playerCount;i++) {
					printPlayerStats(&game.player[i]);

				}

				printLine();
			}
			int roundChoice;
			if (!getIntInput("继续游戏请输入1，退出请输入0 ", 0, 1, &roundChoice)) {
				break;
			}
			else if (roundChoice == 0) {
				break;
			}
		}
		clearGame(&game);
	}
	return 0;
}