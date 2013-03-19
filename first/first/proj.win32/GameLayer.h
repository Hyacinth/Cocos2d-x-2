#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	GameLayer(void);
	virtual ~GameLayer(void);

	bool init(void);

	LAYER_NODE_FUNC(GameLayer);

	virtual void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent *pEvent);

private:
	cocos2d::CCTime time;
	cocos2d::CCSprite *flight;

	void step(cocos2d::CCTime dt);
};

#endif