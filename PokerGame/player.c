#include"player.h"
#include<string.h>

void initPlayer(Player* player) {
	if (player == NULL) {
		return;
	}
	player->name[0] = '\0';
	initHand(&player->hand);

	player->roundsPlayed = 0;
	player->wins = 0;
}

int setPlayername(Player* player,const char* name) {
	if (player == NULL || name == NULL) {
		return 0;
	}
	if (strlen(name) >= NAME_LENGTH) {
		return 0;
	}
	strcpy(player->name, name);
	return 1;
}

int receiveCard(Player* player, Card card) {
	if (player == NULL) {
		return 0;
	}
	return addCard(&player->hand, card);
}

void clearPlayercard(Player* player) {
	if (player == NULL) {
		return;
	}
	initHand(&player->hand);

}