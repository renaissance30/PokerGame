#include"game.h"
#include <stdio.h>
#include<string.h>


void initGame(Game* game) {
	if (game == NULL) {
		return;
	}
	game->mode = GAME_UNSET;
	game->playerCount = 0;

	for (int i = 0;i < MAX_PLAYERS;i++) {
		initPlayer(&game->player[i]);
	}
}

int setGameMode(Game* game,GameMode mode) {
	if (game == NULL) {
		return 0;
	}
	if (mode != GAME_SINGLE_PLAYER && mode != GAME_MULTIPLAYER&&mode != GAME_HUMAN_VS_COMPUTER) {
		return 0;
	}

	game->mode = mode;
	game->playerCount = 0;
	return 1;
}

int setPlayerCount(Game* game, int count) {
	if (game == NULL||game->mode == GAME_UNSET) {
		return 0;
	}
	else if (game->mode == GAME_SINGLE_PLAYER) {
		if (count != 1) {
			return 0;
		}
		
	}
	else if (game->mode == GAME_HUMAN_VS_COMPUTER) {
		if (count != 2) {
			return 0;
		
		}
	}
	else if (game->mode == GAME_MULTIPLAYER) {
		if (count < MIN_PLAYERS || count > MAX_PLAYERS) {
			return 0;
		}
		
	}
	else {
		return 0;
	}
	game->playerCount = count;
	return 1;

}

int configureAllplayers(Game* game) {
	if (game == NULL) {
		return 0;
	}
	if (game->playerCount <= 0||game->playerCount>MAX_PLAYERS) {
		return 0;
	}
	char name[NAME_LENGTH];
	
	for (int i = 0;i < game->playerCount;i++) {
		printf("请输入玩家 %d 的姓名（直接回车使用默认名字）：", i + 1);

		if (fgets(name, sizeof name, stdin) == NULL) {
			return 0;
		}
		name[strcspn(name, "\n")] = '\0';

		if (name[0] == '\0') {
			if (game->mode == GAME_SINGLE_PLAYER || game->mode == GAME_HUMAN_VS_COMPUTER) {
				snprintf(name, sizeof name, "玩家");
			}
			if (game->mode == GAME_MULTIPLAYER) {
				snprintf(name, sizeof name, "玩家%d", i + 1);
			}
		}
	

		if (!setPlayername(&game->player[i], name)) {
			
			return 0;
		}

		
	}

	return 1;
}

int dealCards(Game* game, Deck* deck) {
	if (game == NULL || deck == NULL) {
		return 0;
	}

	if (game->playerCount <= 0||game->playerCount>MAX_PLAYERS) {
		return 0;
	}

	for (int i = 0;i < HAND_SIZE;i++) {
		for (int j = 0;j < game->playerCount;j++) {
			Card card;
		

			if (!drawCard(deck, &card)) {
				
				return 0;

			}
			if (!receiveCard(&game->player[j], card)) {
				
				return 0;
			}
		}
	}

	return 1;
}

void resetGameRounds(Game* game) {
	if (game == NULL) {
		return;
	}
	for (int i = 0;i < game->playerCount;i++) {
		clearPlayercard(&game->player[i]);
	}
}

int startNewRound(Game* game, Deck* deck) {
	if (game == NULL || deck == NULL) {
		return 0;
	}
	
	initDeck(deck);
	shuffleDeck(deck);

	resetGameRounds(game);

	if (!dealCards(game, deck)) {
		return 0;
	}

	return 1;
}

void updateStatistics(Game* game,const int winners[], int winnerCount) {
	if (game == NULL||winners ==NULL) {
		return;
	}
	if (winnerCount <= 0 || winnerCount > game->playerCount||game->playerCount<=0||game->playerCount>MAX_PLAYERS) {
		return;
	}


	for (int i = 0;i < game->playerCount;i++) {
		game->player[i].roundsPlayed++;
	}
	
	// 检查赢家下标是否合法，并排除重复赢家
	for (int i = 0; i < winnerCount; i++) {

		if (winners[i] < 0 ||
			winners[i] >= game->playerCount) {
			return;
		}

		for (int j = 0; j < i; j++) {
			if (winners[i] == winners[j]) {
				return;
			}
		}
	}
	
	// 所有赢家的获胜次数加一
	for (int i = 0; i < winnerCount; i++) {
		int index = winners[i];

		game->player[index].wins++;
	}

}

void clearGame(Game* game) {
	if (game == NULL) {
		return;
	}

	initGame(game);
}