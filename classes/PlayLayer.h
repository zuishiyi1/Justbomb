#ifndef _PLAYLAYER_H_
#define _PLAYLAYER_H_




#include "cocos2d.h"
USING_NS_CC;

#include "GameDefine.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

class Element;

class PlayLayer :public Layer
{
public:

	PlayLayer();

	CREATE_FUNC(PlayLayer);
	virtual bool init();
	void addElement();
	void addTouch();
	void initmap();
	void createele(int,int);
	Point positionOfItem(int, int);

	virtual void update(float);

	void FillEle();

	void checkAndRemoveEle();

	void markRemove(Element*);

	void removeSprite();

	void getColChain(Element*, std::list<Element*> &list);

	void getRowChain(Element*, std::list<Element*> &list);

	void explodeEle(Element*);

	void baozhawind(Point);

	void showdamage(Point);

	void baozhakulou(Point);

	//元素爆炸后执行的删除函数
	void aec(Node*);

	bool onTouchbegan(Touch*, Event* event);

	void onTouchmoved(Touch*, Event* event);

	Element* sprofpoint(Point*);

	void swapspr();

	void setpause(Ref*);

	void setresume(Ref*);

	void setuseaddwind(Ref*);

	void setusekulouitem(Ref*);

	void setuseclearall(Ref*);

	void mission1(Ref*);
	void mission2(Ref*);
	void mission3(Ref*);

	

private:
	Size m_winsize;
	EventListenerTouchOneByOne* listener;
	SpriteBatchNode* spritesheet;
	Element* map[ROW][COL];
	float mapLBX, mapLBY;

	bool isrun;
	bool isfiilele;
	bool iscantouch;

	bool isrow;

	Element* staele;
	Element* endele;

	//是否在播动画
	bool isAnimation;

	int m_score;

	bool useclearall;
	bool useaddwind;
	bool usekulouitem;

	int mission;
	int windtimes;
	int kuloutimes;

	bool finish;

};






#endif