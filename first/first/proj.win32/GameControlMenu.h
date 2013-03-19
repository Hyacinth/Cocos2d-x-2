#ifndef __GAME_CONTROL_MENU_H__
#define __GAME_CONTROL_MENU_H__

#include "cocos2d.h"

class GameControlMenu : public cocos2d::CCLayer
{
public:
	GameControlMenu(void);
	virtual ~GameControlMenu(void);

	bool init(void);

	void sysMenu(CCObject* pSender);

	LAYER_NODE_FUNC(GameControlMenu);
};

#endif