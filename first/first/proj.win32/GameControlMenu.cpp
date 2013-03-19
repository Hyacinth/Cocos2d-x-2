#include "GameControlMenu.h"
#include "SysMenu.h"

using namespace cocos2d;

GameControlMenu::GameControlMenu(void)
{

}

GameControlMenu::~GameControlMenu(void)
{

}

bool GameControlMenu::init(void)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		CCMenuItemFont::setFontSize(22);
		CCMenuItemFont* systemMenu = CCMenuItemFont::itemWithString("Main Menu", this, menu_selector(GameControlMenu::sysMenu));
		CC_BREAK_IF(!systemMenu);

		CCMenu* menu = CCMenu::menuWithItems(systemMenu, NULL);
		CC_BREAK_IF(!menu);

		menu->setPosition(ccp(0, 0));

		systemMenu->setAnchorPoint(ccp(0, 0));
		systemMenu->setPosition(ccp(0, 0));
		this->addChild(menu, 1, 2);

		bRet = true;

	} while (false);

	return bRet;
}

void GameControlMenu::sysMenu(CCObject* pSender)
{
	CCScene* scene = CCScene::node();
	scene->addChild(SysMenu::node());
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::transitionWithDuration(1.2f, scene));
}