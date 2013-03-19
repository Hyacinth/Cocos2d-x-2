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

		// ��Ϸ��������ͼ
		CCSprite *bg = CCSprite::spriteWithFile("Space.png");
		CC_BREAK_IF(!bg);
		bg->setAnchorPoint(CCPointZero);
		// Ϊ��ͻ����Ϸ�����еľ��飬������ɫ�ʱ䵭
		bg->setOpacity(100);
		this->addChild(bg, 0, 1);

		// ʹ��λͼ������ʾ��Ϸʱ��
		CCLabelBMFont* lbScore = CCLabelBMFont::labelWithString("Time: 0", "font09.fnt");
		CC_BREAK_IF(!lbScore);
		lbScore->setAnchorPoint(ccp(1, 1));
		lbScore->setScale(0.6f);
		this->addChild(lbScore, 1, 3);
		lbScore->setPosition(ccp(310, 450));

		// ����ɴ�ͼ��
		CCSpriteBatchNode* mgr = CCSpriteBatchNode::batchNodeWithFile("flight.png", 5);
		CC_BREAK_IF(!mgr);
		this->addChild(mgr, 0, 4);

		// ��״̬����ʾһ���ɴ���ͼ��
		CCSprite* sprite = CCSprite::spriteWithTexture(mgr->getTexture(), CCRectMake)
	} while (false);
}