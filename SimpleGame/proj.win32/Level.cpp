#include "Level.h"


Level::Level(void)
{
}


Level::~Level(void)
{
}

bool Level::initWithLevelNum( int levelNum, float secsPerSpawn, cocos2d::ccColor4B backgroundColor )
{
	this->_levelNum = levelNum;
	this->_secsPerSpawn = secsPerSpawn;
	this->_backgroundColor = backgroundColor;
	return true;
}
