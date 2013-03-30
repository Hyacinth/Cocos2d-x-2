#include "ActionSprite.h"


ActionSprite::ActionSprite(void)
{
	_idleAction = NULL;
	_attackAction = NULL;
	_walkAction = NULL;
	_hurtAction = NULL;
	_knockedOutAction = NULL;
}


ActionSprite::~ActionSprite(void)
{
}

