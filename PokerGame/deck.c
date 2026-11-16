#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"deck.h"

void initDeck(Deck* deck) {
	if (deck == NULL) {
		return;
	}
	int index = 0;
	for (int suit = 0;suit < SUIT_COUNT;suit++) {
		for (int rank = 1;rank < RANK_COUNT;rank++) {
			deck->cards[index].suit = suit;
			deck->cards[index].rank = rank;
			index++;
		}
	}
	deck->top = 0;
}
void swap(Card* a, Card* b) {
	Card temp ;
	temp = *a;
	*a = *b;
	*b = temp;
}

void shuffleDeck(Deck* deck) {
	
	if (deck == NULL) {
		return;
	}

	for (int i = DECK_SIZE - 1;i > 0;i--) {
		int j = rand() % (i + 1);
		swap(&deck->cards[i], &deck->cards[j]);
	}

}

int drawCard(Deck* deck, Card* out) {
	if (deck == NULL || out == NULL) {
		return 0;
	}
	if (deck->top >= DECK_SIZE) {
		return 0;
	}
	
	*out = deck->cards[deck->top];
	deck->top++;
	return 1;
}

int getRemainingCards(const Deck* deck) {
	if (deck == NULL || deck->top<0 || deck->top>DECK_SIZE) {
		return -1;
	}
	return DECK_SIZE - deck->top;
}

void resetDeck(Deck* deck) {
	if (deck == NULL) {
		return;
	}
	initDeck(deck);
	shuffleDeck(deck);
}
