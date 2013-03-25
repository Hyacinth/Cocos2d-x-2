#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)));

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* player = CCSprite::create("player.png", CCRectMake(0, 0, 27, 40));
		CC_BREAK_IF(! player);
		player->setPosition(ccp(player->getContentSize().width/2, winSize.height/2));
		this->addChild(player);

        bRet = true;
    } while (0);

	// Ìí¼Ó¶¨Ê±Æ÷
	this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0);

	this->setTouchEnabled(true);
    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void HelloWorld::addMonster()
{
	CCSprite* monster = CCSprite::create("monster.png");
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = monster->getContentSize().height / 2;
	int maxY = winSize.height - monster->getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (rand() % rangeY) + minY;

	monster->setPosition(ccp(winSize.width + monster->getContentSize().width / 2, actualY));
	this->addChild(monster);

	int minDuration = 2.0;
	int maxDuration = 4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	CCMoveTo* actionMove = CCMoveTo::create(actualDuration, ccp(-monster->getContentSize().width / 2, actualY));
	CCCallFuncN* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::spriteMoveFinished));
	monster->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void HelloWorld::spriteMoveFinished( CCNode* sender )
{
	CCSprite* sprite = (CCSprite*)sender;
	this->removeChild(sprite, true);
}

void HelloWorld::gameLogic( float dt )
{
	this->addMonster();
}


void HelloWorld::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = this->convertTouchToNodeSpace(touch);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* projectile = CCSprite::create("projectile.png");
	projectile->setPosition(ccp(20, winSize.height/2));

	CCPoint offset = ccpSub(location, projectile->getPosition());

	if (offset.x <= 0)
	{
		return;
	}

	this->addChild(projectile);

	int realX = winSize.width + projectile->getContentSize().width/2;
	float ratio = (float)offset.y / (float)offset.x;
	int realY = realX * ratio + projectile->getPosition().y;
	CCPoint realDest = ccp(realX, realY);

	int offRealX = realX - projectile->getPosition().x;
	int offRealY = realY - projectile->getPosition().y;
	float length = sqrtf(offRealX * offRealX + offRealY * offRealY);
	float velocity = 480 / 1;
	float realMoveDuration = length / velocity;

	projectile->runAction(CCSequence::create(CCMoveTo::create(realMoveDuration, realDest), 
		CCCallFuncN::create(this, callfuncN_selector(HelloWorld::spriteMoveFinished)), NULL));

}



