#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "SimpleDPad.h"
#include "HudLayer.h"

using namespace cocos2d;

class GameLayer : public cocos2d::CCLayer, public SimpleDPadDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC(GameLayer);

	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	bool init();
	void initTileMap();
	void initHero();

	void update(float dt);
	void updatePositions();

	virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
	virtual void isHoldingDirection(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
	virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad);

	CC_SYNTHESIZE(HudLayer*, _hud, Hud);

	cocos2d::CCTMXTiledMap* _tileMap;
	cocos2d::CCSpriteBatchNode* _actors;

	Hero* _hero;
};

