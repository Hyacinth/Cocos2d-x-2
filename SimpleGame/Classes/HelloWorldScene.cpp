#include "HelloWorldScene.h"
#include "GameOverLayer.h"
#include "Monster.h"
#include "LevelManager.h"

using namespace cocos2d;


HelloWorld::HelloWorld()
{
	_monsters = NULL;
	_projectiles = NULL;

	_monstersDestroyed = 0;

	_player = NULL;
	_nextProjectile = NULL;
}

HelloWorld::~HelloWorld()
{
	if (_monsters)
	{
		_monsters->release();
		_monsters = NULL;
	}
	if (_projectiles)
	{
		_projectiles->release();
		_projectiles = NULL;
	}
}

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
		this->_monsters = CCArray::create();
		this->_monsters->retain();
		this->_projectiles = CCArray::create();
		this->_projectiles->retain();

		CC_BREAK_IF(! CCLayerColor::initWithColor(LevelManager::sharedInstance()->curLevel()->getBackgroundColor()));

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		_player = CCSprite::create("player2.png");
		_player->setPosition(ccp(_player->getContentSize().width / 2, winSize.height / 2));
		CC_BREAK_IF(! _player);
		this->addChild(_player);

        bRet = true;
    } while (0);

	// 添加定时器
	this->schedule(schedule_selector(HelloWorld::gameLogic), LevelManager::sharedInstance()->curLevel()->getSecsPerSpawn());
	this->schedule(schedule_selector(HelloWorld::update));

	// 背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav");

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
	// CCSprite* monster = CCSprite::create("monster.png");
	Monster* monster = NULL;
	if (rand() % 2 == 0)
	{
		monster = WeakAndFastMonster::create();
	}
	else
	{
		monster = StrongAndSlowMonster::create();
	}
	
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = monster->getContentSize().height / 2;
	int maxY = winSize.height - monster->getContentSize().height / 2;
	int rangeY = maxY - minY;
	int actualY = (rand() % rangeY) + minY;

	monster->setPosition(ccp(winSize.width + monster->getContentSize().width / 2, actualY));
	this->addChild(monster);

	int minDuration = monster->getMinMoveDuration();
	int maxDuration = monster->getMaxMoveDuration();
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	CCMoveTo* actionMove = CCMoveTo::create(actualDuration, ccp(-monster->getContentSize().width / 2, actualY));
	CCCallFuncN* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::spriteMoveFinished));
	monster->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

	monster->setTag(1);
	_monsters->addObject(monster);
}

void HelloWorld::spriteMoveFinished( CCNode* sender )
{
	CCSprite* sprite = (CCSprite*)sender;
	this->removeChild(sprite, true);

	if (sprite->getTag() == 1)
	{
		_monsters->removeObject(sprite);
		// 有怪物跑到左边屏幕，则判定为玩家失败
		CCScene* gameOverScene = GameOverLayer::sceneWithWon(false);
		CCDirector::sharedDirector()->replaceScene(gameOverScene);
	}
	else if (sprite->getTag() == 2)
	{
		_projectiles->removeObject(sprite);
	}
	
}

void HelloWorld::gameLogic( float dt )
{
	this->addMonster();
}


void HelloWorld::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	if (_nextProjectile != NULL)
	{
		return;
	}
	
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	CCPoint location = this->convertTouchToNodeSpace(touch);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_nextProjectile = CCSprite::create("projectile2.png");
	_nextProjectile->retain();
	_nextProjectile->setPosition(ccp(20, winSize.height/2));

	CCPoint offset = ccpSub(location, _nextProjectile->getPosition());

	if (offset.x <= 0)
	{
		return;
	}

	int realX = winSize.width + _nextProjectile->getContentSize().width/2;
	float ratio = (float)offset.y / (float)offset.x;
	int realY = realX * ratio + _nextProjectile->getPosition().y;
	CCPoint realDest = ccp(realX, realY);

	int offRealX = realX - _nextProjectile->getPosition().x;
	int offRealY = realY - _nextProjectile->getPosition().y;
	float length = sqrtf(offRealX * offRealX + offRealY * offRealY);
	float velocity = 480 / 1;
	float realMoveDuration = length / velocity;

	// 计算角度
	float angleRadians = atanf((float)offRealY / (float)offRealX);
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	float cocosAngle = -1 * angleDegrees;
	float rotateDegreesPerSecond = 180 / 0.5;
	float degreesDiff = _player->getRotation() - cocosAngle;
	float rotateDuration = fabs(degreesDiff / rotateDegreesPerSecond);

	_player->runAction(CCSequence::create(CCRotateTo::create(rotateDuration, cocosAngle), 
		CCCallFunc::create(this, callfunc_selector(HelloWorld::finishShoot)), NULL));

	_nextProjectile->runAction(CCSequence::create(CCMoveTo::create(realMoveDuration, realDest), 
		CCCallFuncN::create(this, callfuncN_selector(HelloWorld::spriteMoveFinished)), NULL));
	
	_nextProjectile->setTag(2);

	// 音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
}

void HelloWorld::update( float dt )
{
	CCArray* projectilesToDelete = CCArray::create();
	
	CCObject* pObject = NULL;
	CCObject* pObject2 = NULL;

	CCARRAY_FOREACH(_projectiles, pObject)
	{
		CCSprite* projectile = (CCSprite*)pObject;

		bool monsterHit = false;
		CCArray* monstersToDelete = CCArray::create();

		CCARRAY_FOREACH(_monsters, pObject2)
		{
			Monster* monster = (Monster*)pObject2;
			if (CCRect::CCRectIntersectsRect(projectile->boundingBox(), monster->boundingBox()))
			{
				monsterHit = true;
				monster->setHp(monster->getHp() - 1);
				if (monster->getHp() <= 0)
				{
					monstersToDelete->addObject(monster);
				}
				break;
			}
		}

		CCARRAY_FOREACH(monstersToDelete, pObject2)
		{
			CCSprite* monster = (CCSprite*)pObject2;
			_monsters->removeObject(monster);
			this->removeChild(monster, true);
			// 计算消灭怪物总数，判断胜利条件
			_monstersDestroyed++;
			if (_monstersDestroyed > 10)
			{
				CCScene* gameOverScene = GameOverLayer::sceneWithWon(true);
				CCDirector::sharedDirector()->replaceScene(gameOverScene);
			}
		}

		if (monsterHit)
		{
			projectilesToDelete->addObject(projectile);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
		}
		
	}

	CCARRAY_FOREACH(projectilesToDelete, pObject)
	{
		CCSprite* projectile = (CCSprite*)pObject;
		_projectiles->removeObject(projectile);
		this->removeChild(projectile, true);
	}

	projectilesToDelete->release();
}

void HelloWorld::finishShoot()
{
	this->addChild(_nextProjectile);
	_projectiles->addObject(_nextProjectile);

	_nextProjectile->release();
	_nextProjectile = NULL;
}




