#ifndef _CELL_H_
#define _CELL_H_

#include "cocos2d.h"
USING_NS_CC;

#include "GameDefine.h"

class Cell :public Layer
{
public:
	CREATE_FUNC(Cell);
	virtual bool init();
	void addCell();
private:
	Sprite* cell;
	Size m_winsize;
	int m_cellnum;
	float mapLBX;
	float mapLBY;
};







#endif