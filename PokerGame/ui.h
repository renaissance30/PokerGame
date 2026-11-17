#pragma once
#include "card.h"
#include "hand.h"
#include "player.h"
#include "game.h"

/**清理屏幕，初始化。*/
void clearScreen(void);

//---------------手牌展示--------------//
/**渲染一张扑克牌的外观。*/
void renderCard(const Card* card, int faceUp);

/**渲染一副全部手牌。*/
void renderHand(const Hand* hand);

//-------------游戏界面展示-----------//

/**渲染游戏菜单。*/
void renderMainMenu(void);

/**渲染出结尾效果。*/
void renderGameOver(void);

/**渲染出游戏控制台。*/
void renderGameTable(const Game* game);