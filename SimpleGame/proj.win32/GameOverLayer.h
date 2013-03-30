#pragma once
#include "cocos2d.h"

class GameOverLayer :
	public cocos2d::CCLayerColor
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);

	bool initWithWon(bool won);

	static cocos2d::CCScene* sceneWithWon(bool won);
	static GameOverLayer* createWithWon(bool won);
	void gameOverDone();
};

