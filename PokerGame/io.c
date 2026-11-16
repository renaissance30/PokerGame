#include"io.h"
#include"game.h"
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<ctype.h>
#include<limits.h>
#include<stddef.h>
#include<string.h>

int getIntInput(const char* prompt, int min, int max,int* outValue) {

	while (1){              //实现只有输入合法才继续，输入不合法就一直要求重输
		printf("%s", prompt);
		char buffer[100];   //第一个缓冲数组，如用scanf来实现输入有可能会出现例如“1abc”只读到1的情况
		if (fgets(buffer, sizeof buffer, stdin) == NULL) {
			return 0;
		}
		char* endptr;
		long num = strtol(buffer, &endptr, 10);

		// 检查 long 转换是否溢出
		if (errno == ERANGE) {
			printf("输入数值过大或过小！\n");
			continue;
		}

		while (isspace((unsigned char)*endptr)) {
			endptr++;       //如果输入的数字后面有空格且空格后面没有非'\0'输入，那么也理应接受这个输入
		}
		if (*endptr != '\0') {
			printf("您的输入不合法！\n");
			continue;
		}
		// 检查 int 类型范围
		if (num < INT_MIN || num > INT_MAX) {
			printf("输入数值超出 int 范围！\n");
			continue;
		}

	    //检测输入是否在我们规定的最大值和最小值中间
		if (num<min || num>max) {
			printf("您的输入超过允许范围！\n");
			continue;
		}
		
		*outValue = num;
		return 1;
	}
}

int getStringInput(const char* prompt, char* buffer, size_t size) {
	while (1) {
		printf("%s", prompt);
		
		if (fgets(buffer, size, stdin) == NULL) {
			return 0;
		}
		char* newline = strchr(buffer, '\n');
		if (newline != NULL) {
			*newline = '\0';
		}
		else { 
			int ch = getchar();
			if (ch != '\n' && ch != EOF) {
				while ((ch = getchar()) != '\n' && ch != EOF) {
				}
				printf("输入内容过长，请重新输入！\n");
				continue;
			}
		}
		return 1;
	}
}

void printLine(void)
{
	for (int i = 0; i < UI_WIDTH; i++) {
		printf("=");
	}
	printf("\n");
}

static int isWideCharacter(unsigned int cp)
{
    return
        (cp >= 0x1100 && cp <= 0x115F) ||
        (cp >= 0x2E80 && cp <= 0xA4CF) ||
        (cp >= 0xAC00 && cp <= 0xD7A3) ||
        (cp >= 0xF900 && cp <= 0xFAFF) ||
        (cp >= 0xFE10 && cp <= 0xFE6F) ||
        (cp >= 0xFF00 && cp <= 0xFF60) ||
        (cp >= 0xFFE0 && cp <= 0xFFE6) ||
        (cp >= 0x1F300 && cp <= 0x1FAFF) ||
        (cp >= 0x20000 && cp <= 0x3FFFD);
}

/* 计算 UTF-8 字符串的显示宽度 */
int getDisplayWidth(const char* str)
{
    if (str == NULL) {
        return 0;
    }

    int width = 0;
    const unsigned char* p = (const unsigned char*)str;

    while (*p != '\0') {
        unsigned int cp;

        if (*p < 0x80) {
            cp = *p;
            p += 1;
        }
        else if ((*p & 0xE0) == 0xC0 &&
            (p[1] & 0xC0) == 0x80) {
            cp = ((p[0] & 0x1F) << 6) |
                (p[1] & 0x3F);
            p += 2;
        }
        else if ((*p & 0xF0) == 0xE0 &&
            (p[1] & 0xC0) == 0x80 &&
            (p[2] & 0xC0) == 0x80) {
            cp = ((p[0] & 0x0F) << 12) |
                ((p[1] & 0x3F) << 6) |
                (p[2] & 0x3F);
            p += 3;
        }
        else if ((*p & 0xF8) == 0xF0 &&
            (p[1] & 0xC0) == 0x80 &&
            (p[2] & 0xC0) == 0x80 &&
            (p[3] & 0xC0) == 0x80) {
            cp = ((p[0] & 0x07) << 18) |
                ((p[1] & 0x3F) << 12) |
                ((p[2] & 0x3F) << 6) |
                (p[3] & 0x3F);
            p += 4;
        }
        else {
            /* 遇到不合法的 UTF-8 字节 */
            width++;
            p++;
            continue;
        }

        width += isWideCharacter(cp) ? 2 : 1;
    }

    return width;
}

/* 输出居中的字符串 */
void printCentered(const char* str)
{
    if (str == NULL) {
        return;
    }

    int width = getDisplayWidth(str);

    int spaces = (UI_WIDTH - width) / 2;

    if (spaces < 0) {
        spaces = 0;
    }

    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }

    printf("%s\n", str);
}



void printWelcome(void) {
    printLine();
    printCentered("扑克牌游戏");
    printf("\n");
    printCentered("欢迎来到扑克牌游戏");
    printLine();
}

void printMenu(void) {
    printf("\n");
    printCentered("1.单人模式");
    printCentered("2.多人对战");
    printCentered("3.人机对战");
    printCentered("4.退出游戏");
    printf("\n");
    printLine();
}
void printCard(const Card* card) {
    if (card == NULL) {
        return;
    }
    printf("%s %s", getSuitString(card->suit), getRankString(card->rank));
}

void printHand(const Hand* hand) {
    if (hand == NULL) {
        return;
    }
    for (int i = 0;i < hand->count;i++) {
        printCard(&hand->cards[i]);
        printf("   ");
    }
}

void printHandRank(const Result* result) {
   if (result == NULL) {
        return;
   }
   switch (result->HandRank) {
    case(HIGH_CARD):
        printf("高牌");
        break;
    case(ONE_PAIR):
        printf("一对");
        break;
    case(TWO_PAIR):
        printf("两对");
        break;
    case(THREE):
        printf("三条");
        break;
    case(STRAIGHT):
        printf("顺子");
        break;
    case(FLUSH):
        printf("同花");
        break;
    case(FULL_HOUSE):
        printf("三拖二");
        break;
    case(FOUR):
        printf("四炸");
        break;
    case(STRAIGHT_FLUSH):
        printf("同花顺");
        break;
    case(ROYAL_FLUSH):
        printf("皇家同花顺");
        break;
    default:
        printf("未知牌型");
        break;
   }

}

void printPlayerStats(const Player* player) {
    if (player == NULL) {
        return;
    }
    printf("玩家%s：\n", player->name);
    printf("参与场数：%d\n", player->roundsPlayed);
    printf("累计胜场：%d\n", player->wins);

    if (player->roundsPlayed > 0) {
        printf("玩家胜率：%.2f%%\n", 100.0 * player->wins / player->roundsPlayed);
    }
    else {
        printf("玩家胜率：暂无数据\n");
    }

}