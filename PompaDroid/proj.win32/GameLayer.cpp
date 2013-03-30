#include "GameLayer.h"
using namespace cocos2d;

GameLayer::GameLayer( void )
{
	_tileMap = NULL;
}

GameLayer::~GameLayer( void )
{

}

bool GameLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		this->initTileMap();

		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
		_actors = CCSpriteBatchNode::create("pd_sprites.pvr.ccz");
		_actors->getTexture()->setAliasTexParameters();
		this->addChild(_actors, -5);

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