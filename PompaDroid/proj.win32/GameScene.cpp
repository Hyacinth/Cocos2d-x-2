#include "GameScene.h"


GameScene::GameScene(void)
{
	_gameLayer = NULL;
	_hudLayer = NULL;
}


GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		_gameLayer = GameLayer::create();
		this->addChild(_gameLayer, 0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer, 1);

		bRet = true;
	} while (0);

	return bRet;
}
