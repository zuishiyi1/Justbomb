#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include "cocos2d.h"
USING_NS_CC;

#include "GameDefine.h"
class Item;

class Package :public Layer
{
public:
	CREATE_FUNC(Package);
	virtual bool init();
	void openPackage(Ref*);
	void closePackage(Ref*);
	bool ontouchbegan(Touch*, Event*);
	void inititem();
	void createitem(int,int);
	void useaddwind(Ref*);
	void usekulouitem(Ref*);
	void useclearall(Ref*);

private:
	Size m_winsize;
	Menu* menu;
	MenuItemImage* packageitem;
	EventListenerTouchOneByOne* listener;
	Sprite* pk;
	Item* itemmap[6][5];
	MenuItemImage* addwinditem;
	int addwindnum;
	MenuItemImage* kulouitem;
	int kulouitemnum;
	MenuItemImage* clearallitem;
	int clearallnum;

};






#endif