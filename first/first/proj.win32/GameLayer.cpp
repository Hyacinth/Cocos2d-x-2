#include "GameLayer.h"
#include "SysMenu.h"

using namespace cocos2d;

GameLayer::GameLayer(void)
	: time(0.0f), flight(NULL)
{

}

GameLayer::~GameLayer(void)
{

}

bool GameLayer::init(void)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		// 游戏场景背景图
		CCSprite *bg = CCSprite::spriteWithFile("Space.png");
		CC_BREAK_IF(!bg);
		bg->setAnchorPoint(CCPointZero);
		// 为了突出游戏场景中的精灵，将背景色彩变淡
		bg->setOpacity(100);
		this->addChild(bg, 0, 1);

		// 使用位图字体显示游戏时间
		CCLabelBMFont* lbScore = CCLabelBMFont::labelWithString("Time: 0", "font09.fnt");
		CC_BREAK_IF(!lbScore);
		lbScore->setAnchorPoint(ccp(1, 1));
		lbScore->setScale(0.6f);
		this->addChild(lbScore, 1, 3);
		lbScore->setPosition(ccp(310, 450));

		// 载入飞船图像集
		CCSpriteBatchNode* mgr = CCSpriteBatchNode::batchNodeWithFile("flight.png", 5);
		CC_BREAK_IF(!mgr);
		this->addChild(mgr, 0, 4);

		// 在状态栏显示一个飞船的图标
		CCSprite* sprite = CCSprite::spriteWithTexture(mgr->getTexture(), CCRectMake)
	} while (false);
}