#pragma once

#define DECK_SIZE 52

/** 四种花色。 */
typedef enum {
    SUIT_HEARTS = 0,  /**< 红桃 */
    SUIT_SPADES,      /**< 黑桃 */
    SUIT_CLUBS,       /**< 梅花 */
    SUIT_DIAMONDS,    /**< 方块 */
    SUIT_COUNT        /**< 花色数量，仅用于循环和数组大小。 */
} Suit;

/** 十三个点数，显式写出便于阅读和调试。 */
typedef enum {
    RANK_ACE = 1,
    RANK_TWO = 2,
    RANK_THREE = 3,
    RANK_FOUR = 4,
    RANK_FIVE = 5,
    RANK_SIX = 6,
    RANK_SEVEN = 7,
    RANK_EIGHT = 8,
    RANK_NINE = 9,
    RANK_TEN = 10,
    RANK_JACK = 11,
    RANK_QUEEN = 12,
    RANK_KING = 13,
    RANK_COUNT =14

} Rank;
/** 一张扑克牌。 */
typedef struct {
    Suit suit;
    Rank rank;
} Card;

const char* getSuitString(Suit suit);
const char* getRankString(Rank rank);


