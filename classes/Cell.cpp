#include "Cell.h"
bool Cell::init()
{
	if (!Layer::init()) return false;

	m_winsize = Director::getInstance()->getVisibleSize();

	mapLBX = (m_winsize.width - 30 * COL - (COL - 1) * 2) / 2;
	mapLBY = (m_winsize.height - 30 * ROW - (ROW - 1) * 2) / 2;

	switch ((int)(CCRANDOM_0_1() * 10) - 5)
	{
	case 0:
		m_cellnum = 1;
		break;
	case 1:
		m_cellnum = 2;
		break;
	case 2:
		m_cellnum = 3;
		break;
	case 3:
		m_cellnum = 4;
		break;
	case 4:
		m_cellnum = 5;
		break;
	default:
		m_cellnum = 1;
		break;
	};



	


	addCell();


	
	return true;
}


void Cell::addCell()
{
	

	

	for (int j = 0; j <ROW; j++)
	{
	
	for (int i = 0; i <COL; i++)
	{
		auto moveto = MoveTo::create(1.0f, Point(mapLBX + (30 + 2) * i + 30 / 2, mapLBY + (30 + 2) * j + 30 / 2));  //必定要落到的地方
		auto delay = DelayTime::create(1.5f);
		auto seq = Sequence::create(delay, moveto,  NULL);
		Sprite* nextcell = Sprite::create(StringUtils::format("background/cell%d.png",m_cellnum));
		nextcell->setOpacity(125);
		this->addChild(nextcell);
		nextcell->setPosition(Point(i, m_winsize.height - (CCRANDOM_0_1()*1000) - j-m_winsize.height));  //初始位置
		nextcell->runAction(seq);
		
	}

	}
	

}
