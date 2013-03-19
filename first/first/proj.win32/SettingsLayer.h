#ifndef __SETTINGS_LAYER_H__
#define __SETTINGS_LAYER_H__

#include "cocos2d.h"

class SettingsLayer : public cocos2d::CCLayer
{
public:
	SettingsLayer(void);
	virtual ~SettingsLayer(void);

	bool init(void);

	BOID backCallback(CCObject* pSender);

	LAYER_NODE_FUNC(SettingsLayer);
};

#endif