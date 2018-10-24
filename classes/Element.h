#ifndef _ELEMENT_H_
#define _ELEMENT_H_


#include "cocos2d.h"
USING_NS_CC;

#include "GameDefine.h"

class Element :public Sprite
{
public:
	static Element* create(int, int);
	Element();
	
	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int,m_col,Col);
	CC_SYNTHESIZE(int, m_imgindex, Imgindex);
	CC_SYNTHESIZE(bool, m_check, IgnoreCheck);
	CC_SYNTHESIZE(bool, m_isneedremove, IsNeedRemove);
	CC_SYNTHESIZE_READONLY(DisplayMode, m_mode, Displaymode);

	void setmode(DisplayMode);



};






#endif