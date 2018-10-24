#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "cocos2d.h"
//USING_NS_CC;



class MainScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(MainScene);
	virtual bool init();
	void addEffect();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

};






#endif