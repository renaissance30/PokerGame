#include<stdio.h>
#include"hand.h"
#include"card.h"
#include"deck.h"


void initHand(Hand* hand) {
	if (hand == NULL) {
		return;
	}
	hand->count = 0;
}

int addCard(Hand* hand, Card card) {
	if (hand == NULL) {
		return 0;
	}
	if (hand->count<0 || hand->count>=HAND_SIZE) {
		return 0;
	}

	hand->cards[hand->count] = card;
	hand->count++;
	return 1;
}

void sortHand(Hand* hand) {
	if (hand == NULL) {
		return;
	}
	for (int i = 0;i < HAND_SIZE - 1;i++) {
		for (int j = 0;j < HAND_SIZE - 1 - i;j++) {
			if (hand->cards[j].rank < hand->cards[j + 1].rank) {
				Card temp = hand->cards[j];
				hand->cards[j] = hand->cards[j + 1];
				hand->cards[j + 1] = temp;
			}
		}
	}
}