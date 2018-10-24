#include "Element.h"

Element::Element() :
m_row(0),
m_col(0),
m_imgindex(0),
m_isneedremove(false)
{

}


Element* Element::create(int row, int col)
{
	Element* element = new Element();
	element->m_row = row;
	element->m_col = col;
	element->m_imgindex = rand() % 5;
	element->initWithSpriteFrameName(elementnormal[element->m_imgindex]);
	element->autorelease();
	return element;
}


void Element::setmode(DisplayMode mode)
{
	m_mode = mode;

	SpriteFrame* frame;

	switch (m_mode)
	{
	case fire:
		frame=SpriteFrameCache::getInstance()->getSpriteFrameByName(elementfire);
		m_imgindex = 6;
		break;
	case dark:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(elementdark);
		m_imgindex = 7;
		break;
	case damage:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(elementdamage);
		m_imgindex = 8;
		break;
	case wind:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(elementwind);
		m_imgindex = 9;
		break;
	case land:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(elementland);
		m_imgindex = 10;
		break;
	case normal:
		m_imgindex = rand() % 5;
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(elementnormal[m_imgindex]);
		break;

	default:
		break;
	}
    setDisplayFrame(frame);
}