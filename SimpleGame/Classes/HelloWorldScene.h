#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayerColor
{
public:
	HelloWorld();
	~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void addMonster();
	void spriteMoveFinished(CCNode* sender);
	void gameLogic(float dt);
	void update(float dt);
	void finishShoot();

	// жиди
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	cocos2d::CCArray* _monsters;
	cocos2d::CCArray* _projectiles;
	cocos2d::CCSprite* _player;
	cocos2d::CCSprite* _nextProjectile;

private:
	int _monstersDestroyed;
};

#endif  // __HELLOWORLD_SCENE_H__