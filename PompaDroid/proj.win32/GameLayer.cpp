#include "GameLayer.h"
#include "GameScene.h"
using namespace cocos2d;

GameLayer::GameLayer( void )
{
	_tileMap = NULL;
	_hero = NULL;
}

GameLayer::~GameLayer( void )
{
	this->unscheduleUpdate();
}

bool GameLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		this->setTouchEnabled(true);

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
		_actors = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
		_actors->getTexture()->setAliasTexParameters();
		this->addChild(_actors, -5);

		this->initHero();
		this->initTileMap();
		this->scheduleUpdate();

		bRet = true;
	} while (false);

	return bRet;
}

void GameLayer::initTileMap()
{
	_tileMap = CCTMXTiledMap::create("pd_tilemap.tmx");
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
	{
		CCTMXLayer* child = (CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap, -6);
}

void GameLayer::initHero()
{
	_hero = Hero::create();
	_actors->addChild(_hero);
	_hero->setPosition(ccp(_hero->getCenterToSides(), 80));
	_hero->setDesiredPosition(_hero->getPosition());
	_hero->idle();
}

void GameLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	_hero->attack();
}

void GameLayer::didChangeDirectionTo( SimpleDPad *simpleDPad, cocos2d::CCPoint direction )
{
	_hero->walkWithDirection(direction);
}

void GameLayer::isHoldingDirection( SimpleDPad *simpleDPad, cocos2d::CCPoint direction )
{
	_hero->walkWithDirection(direction);
}

void GameLayer::simpleDPadTouchEnded( SimpleDPad *simpleDPad )
{
	if (_hero->getActionState() == kActionStateWalk)
	{
		_hero->idle();
	}
}

void GameLayer::update( float dt )
{
	_hero->update(dt);
	this->updatePositions();
}

void GameLayer::updatePositions()
{
	float posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - _hero->getCenterToSides(),
		MAX(_hero->getCenterToSides(), )
}

