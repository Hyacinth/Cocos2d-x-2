#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "LevelManager.h"

using namespace cocos2d;

GameOverLayer::GameOverLayer(void)
{
}


GameOverLayer::~GameOverLayer(void)
{
}

bool GameOverLayer::initWithWon( bool won )
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)));

		CCString* message;
		if (won)
		{
			LevelManager::sharedInstance()->nextLevel();
			Level* curLevel = LevelManager::sharedInstance()->curLevel();
			if (curLevel)
			{
				message = CCString::createWithFormat("Get ready for level %d", curLevel->getLevelNum());
			}
			else
			{
				message = CCString::create("You Won!");
				LevelManager::sharedInstance()->reset();
			}
		}
		else
		{
			message = CCString::create("You Lose :[");
			LevelManager::sharedInstance()->reset();
		}

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCLabelTTF* label = CCLabelTTF::create(message->getCString(), "Arial", 32);
		label->setColor(ccc3(0, 0, 0));
		label->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(label);

		this->runAction(CCSequence::create(CCDelayTime::create(3), 
			CCCallFunc::create(this, callfunc_selector(GameOverLayer::gameOverDone)), NULL));

		bRet = true;
	} while (false);

	return bRet;
}

cocos2d::CCScene* GameOverLayer::sceneWithWon( bool won )
{
	CCScene* scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		GameOverLayer* layer = GameOverLayer::createWithWon(won);
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (false);

	return scene;
}

GameOverLayer* GameOverLayer::createWithWon( bool won )
{
	GameOverLayer* pRet = new GameOverLayer();
	if (pRet && pRet->initWithWon(won))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

void GameOverLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}
