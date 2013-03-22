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
		CCSprite* sprite = CCSprite::spriteWithTexture(mgr->getTexture(), CCRectMake(0, 0, 31, 30));
		CC_BREAK_IF(!sprite);
		mgr->addChild(sprite, 1, 5);
		sprite->setScale(1.1f);
		sprite->setAnchorPoint(ccp(0, 1));
		sprite->setPosition(ccp(10, 460));

		// ��ʾ��ǰ�ɴ���������
		CCLabelBMFont* lbLife = CCLabelBMFont::labelWithString("3", "font09.fnt");
		CC_BREAK_IF(!lbLife);
		lbLife->setAnchorPoint(ccp(0, 1));
		lbLife->setScale(0.6f);
		this->addChild(lbLife, 1, 6);
		lbLife->setPosition(ccp(50, 450));

		// �趨ʱ��ص��������޸���Ϸ��ʱ��ʾ
		this->schedule(schedule_selector(GameLayer::step), 1.0f);

		// ��ʾ�ɴ����ɴ��в�����˸�Ļ�������Ч��
		flight = CCSprite::spriteWithTexture(mgr->getTexture(), CCRectMake(0, 0, 31, 30));
		CC_BREAK_IF(!flight);
		flight->setPosition(ccp(160, 30));
		flight->setScale(1.6f);
		mgr->addChild(flight, 1, 99);

		// �趨����ÿһ֡������
		CCAnimation* animation = CCAnimation::animation();
		CC_BREAK_IF(!animation);
		animation->setName("flight");
		animation->setDelay(0.2f);
		for (int i = 0; i < 3; ++i)
		{
			int x = i % 3;
			animation->addSpriteFrameWithTexture(mgr->getTexture(), CCRectMake(x*32, 0, 31, 30));
		}

		// ���ڶ�����������
		CCAnimate* action = CCAnimate::actionWithAnimation(animation);
		CC_BREAK_IF(!action);

		// ���Ǿ��鲻���ظ�������ʵ�ֶ�̬����Ч��
		flight->runAction(CCRepeatForever::actionWithAction(action));

		// accept touch now
		this->setTouchEnabled(true);

		bRet = true;
	} while (false);

	return bRet;
}

void GameLayer::ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)pTouches->anyObject();
	// ��ô���������
	CCPoint location = touch->locationInView(touch->getLocationInView());
	CCPoint convertedLocation = CCDirector::sharedDirector()->convertToGL(location);
	// �÷ɴ���1�������ƶ���ȥ
	flight->runAction(CCMoveTo::actionWithDuration(1.0f, ccp(convertedLocation.x, convertedLocation.y)));
}

void GameLayer::step(CCTime dt)
{
	time += dt;
	char time_str[20];
	sprintf(time_str, "Time: %d", (int)time);
	CCLabelBMFont* label1 = (CCLabelBMFont*)this->getChildByTag(3);
	label1->setString(time_str);
}