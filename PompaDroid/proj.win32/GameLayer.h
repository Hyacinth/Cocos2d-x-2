#pragma once
#include "cocos2d.h"

class GameLayer :
	public cocos2d::CCLayer
{
public:
	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC(GameLayer);

	bool init();
	void initTileMap();

	cocos2d::CCTMXTiledMap* _tileMap;
	cocos2d::CCSpriteBatchNode* _actors;
};

