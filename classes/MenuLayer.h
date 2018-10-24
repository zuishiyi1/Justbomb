#ifndef _MENULAYER_H_
#define _MENULAYER_H_


#include "cocos2d.h"
USING_NS_CC;

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class MenuLayer :public Layer
{
public:
	MenuLayer();
	~MenuLayer();
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	void addTitle();
	void addStartBtn();
	void addTouch();
private:
	Size m_winsize;
	Sprite* kaibtn;
	Sprite* shibtn;
	Sprite* youbtn;
	Sprite* xibtn;
	Sprite* title;
	Sprite* shuoming;
	bool sound;
};









#endif