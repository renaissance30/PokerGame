#include <stdio.h>
#include "card.h"

const char* getSuitString(Suit suit) {
	switch (suit) {
	case SUIT_HEARTS:
		return "红桃";
	case SUIT_SPADES:
		return "黑桃";
	case SUIT_CLUBS:
		return "梅花";
	case SUIT_DIAMONDS:
		return "方块";
	default:
		return"未知花色";
	}
}

const char* getRankString(Rank rank) {
	switch (rank) {
	case RANK_ACE:
		return "A";
	case RANK_TWO:
		return "2";
	case RANK_THREE:
		return "3";
	case RANK_FOUR:
		return "4";
	case RANK_FIVE:
		return "5";
	case RANK_SIX:
		return "6";
	case RANK_SEVEN:
		return "7";
	case RANK_EIGHT:
		return "8";
	case RANK_NINE:
		return "9";
	case RANK_TEN:
		return "10";
	case RANK_JACK:
		return "J";
	case RANK_QUEEN:
		return "Q";
	case RANK_KING:
		return "K";
	default:
		return "未知点数";

	}
}

