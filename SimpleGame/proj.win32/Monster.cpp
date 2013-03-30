#include "Monster.h"


Monster::Monster(void)
{
}


Monster::~Monster(void)
{
}

bool Monster::initWithFile( const char* pszFilename, int hp, int minMoveDuration, int maxMoveDuration )
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCSprite::initWithFile(pszFilename));
		this->_hp = hp;
		this->_minMoveDuration = minMoveDuration;
		this->_maxMoveDuration = maxMoveDuration;

		bRet = true;
	} while (0);

	return bRet;
}


bool WeakAndFastMonster::init( void )
{
	return Monster::initWithFile("monster.png", 1, 3, 5);
}

bool StrongAndSlowMonster::init( void )
{
	return Monster::initWithFile("monster2.png", 3, 6, 12);
}
