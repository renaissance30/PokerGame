#include"evaluate.h"
#include<stdio.h>


Result FirstCompare(Card* cards)
{//按从大到小理牌
    int value[5];
    Card temp;
    Result result;

    for (int i = 0; i < 4; i++)
    {
        for (int j = i; j < 5; j++)
        {
            if (cards[i].rank < cards[j].rank)
            {
                temp = cards[i];
                cards[i] = cards[j];
                cards[j] = temp;
            }
        }
    }

    //判断

    //1.判断同花
    int is_flush = 1;
    for (int i = 1; i < 5; i++)
    {
        if (cards[i].suit != cards[0].suit)
        {
            is_flush = 0;
            break;
        }
    }

    //2.普通顺子判断
    int is_straight = 1;
    for (int i = 0; i < 4; i++)
    {
        if (cards[i].rank - cards[i + 1].rank != 1)
        {
            is_straight = 0;
            break;
        }
    }

    //3.特殊顺子
    int special_straight = 0;
    if (cards[0].rank == 5 && cards[1].rank == 4 &&
        cards[2].rank == 3 && cards[3].rank == 2 && cards[4].rank == RANK_ACE)
    {
        special_straight = 1;
    }

    //4.皇家顺子特例
    int royal_straight = 0;
    if (cards[0].rank == 13 && cards[1].rank == 12 &&
        cards[2].rank == 11 && cards[3].rank == 10 && cards[4].rank == RANK_ACE)
    {
        royal_straight = 1;
    }

    //5.统计各个点数出现次数
    int cnt[14] = { 0 };
    for (int i = 0; i < 5; i++)
    {
        cnt[cards[i].rank]++;
    }

    int four_point = -1;    //四条点数
    int three_point = -1;   //三条点数
    int pair1 = -1;         //大对子
    int pair2 = -1;         //小对子


    for (int i = 13; i >= 1; i--)
    {
        if (cnt[i] == 4)
            four_point = i;
        if (cnt[i] == 3)
            three_point = i;
        if (cnt[i] == 2)
        {
            if (pair1 == -1)
                pair1 = i;
            else
                pair2 = i;
        }
    }



    //========================================

    //皇家同花顺
    if (is_flush && royal_straight)
    {
        result.HandRank = ROYAL_FLUSH;
        result.value[0] = 14;
        result.value[1] = 0;
        result.value[2] = 0;
        result.value[3] = 0;
        result.value[4] = 0;
        return result;
    }

    //同花顺
    if (is_flush && (is_straight || special_straight))
    {
        result.HandRank = STRAIGHT_FLUSH;
        if (special_straight)
            result.value[0] = 5;
        else
            result.value[0] = cards[0].rank;

        result.value[1] = 0;
        result.value[2] = 0;
        result.value[3] = 0;
        result.value[4] = 0;
        return result;
    }

    //四条（炸弹）
    if (four_point != -1)
    {
        result.HandRank = FOUR;
        result.value[0] = four_point;
        int single = 0;
        for (int i = 13; i >= 1; i--)
        {
            if (cnt[i] == 1)
            {
                single = i;
                break;
            }
        }
        result.value[1] = single;
        result.value[2] = 0;
        result.value[3] = 0;
        result.value[4] = 0;
        return result;
    }

    //葫芦（三张+一对）
    if (three_point != -1 && pair1 != -1)
    {
        result.HandRank = FULL_HOUSE;
        result.value[0] = three_point;
        result.value[1] = pair1;
        result.value[2] = 0;
        result.value[3] = 0;
        result.value[4] = 0;
        return result;
    }

    //普通同花
    if (is_flush)
    {
        result.HandRank = FLUSH;
        for (int i = 0; i < 5; i++)
        {
            result.value[i] = cards[i].rank;
        }
        return result;
    }

    //普通顺子（含皇家顺子、A 2 3 4 5顺子）
    if (is_straight || special_straight || royal_straight)
    {
        result.HandRank = STRAIGHT;
        if (special_straight)
            result.value[0] = 5;
        else if (royal_straight)
            result.value[0] = 14;
        else
            result.value[0] = cards[0].rank;

        result.value[1] = 0;
        result.value[2] = 0;
        result.value[3] = 0;
        result.value[4] = 0;
        return result;
    }

    //三条
    if (three_point != -1)
    {
        result.HandRank = THREE;
        result.value[0] = three_point;
        int s[2], idx = 0;
        for (int i = 13; i >= 1; i--)
        {
            if (cnt[i] == 1)
            {
                s[idx++] = i;
            }
        }
        result.value[1] = s[0];
        result.value[2] = s[1];
        result.value[3] = 0;
        result.value[4] = 0;
        return result;
    }

    //两对
    if (pair1 != -1 && pair2 != -1)
    {
        result.HandRank = TWO_PAIR;
        result.value[0] = pair1;
        result.value[1] = pair2;
        int single = 0;
        for (int i = 13; i >= 1; i--)
        {
            if (cnt[i] == 1)
            {
                single = i;
                break;
            }
        }
        result.value[2] = single;
        result.value[3] = 0;
        result.value[4] = 0;
        return result;
    }

    //一对
    if (pair1 != -1)
    {
        result.HandRank = ONE_PAIR;
        result.value[0] = pair1;
        int s[3], idx = 0;
        for (int i = 13; i >= 1; i--)
        {
            if (cnt[i] == 1)
            {
                s[idx++] = i;
            }
        }
        result.value[1] = s[0];
        result.value[2] = s[1];
        result.value[3] = s[2];
        result.value[4] = 0;
        return result;
    }

    //高牌
    result.HandRank = HIGH_CARD;
    for (int i = 0; i < 5; i++)
    {
        result.value[i] = cards[i].rank;
    }
    return result;

}


