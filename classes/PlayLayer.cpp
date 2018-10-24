#include "PlayLayer.h"
#include "Element.h"




PlayLayer::PlayLayer():
spritesheet(NULL),
isrun(true),
isfiilele(false),
iscantouch(true),
isAnimation(false),
m_score(0),
useaddwind(false),
useclearall(false),
usekulouitem(false),
mission(0),
windtimes(0),
kuloutimes(0),
finish(false)
{

}




bool PlayLayer::init()
{
	if (!Layer::init()) return false;

	m_winsize = Director::getInstance()->getVisibleSize();

	
	

	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("element/element.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("TeXiao/texiao.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("TeXiao/texiao2.plist");
	spritesheet = SpriteBatchNode::create("element/element.png");
	addChild(spritesheet);

	
	mapLBX = (m_winsize.width - 30 * COL - (COL - 1) * 2) / 2;
	mapLBY = (m_winsize.height - 30 * ROW - (ROW - 1) * 2) / 2;

	TTFConfig config("fonts/DanishCrack.ttf",30);


	Label* score = Label::createWithTTF(config, StringUtils::format("Score: %d", m_score),TextHAlignment::CENTER);
	score->setTag(10);
	score->setPosition(Point(m_winsize.width / 2, m_winsize.height - 50));

	this->addChild(score);

	

	
	
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::setpause), StringUtils::toString(openpk), NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::setresume), StringUtils::toString(closepk), NULL);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::setuseaddwind), StringUtils::toString(state_useaddwinditem), NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::setuseclearall), StringUtils::toString(state_useclearallitem), NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::setusekulouitem), StringUtils::toString(state_usekulouitem), NULL);


	
	initmap();

	this->scheduleUpdate();





	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchbegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchmoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	


	return true;
}



void PlayLayer::initmap()
{
	


		for (int r = 0; r < ROW; r++)
		{
			for (int c = 0; c < COL; c++)
			{
				createele(r, c);
			}
		}
		
	
}


void PlayLayer::createele(int row, int col)
{
	Element* ele = Element::create(row, col);
	
	//��20���ʻ���������
	if ((CCRANDOM_0_1() * 10) < 2)
	{
		ele->setmode(damage);
	}

	// �������䶯��
	Point endPosition = positionOfItem(row, col);
	Point startPosition = Point(endPosition.x, endPosition.y + m_winsize.height / 2);
	ele->setPosition(startPosition);
	float speed = startPosition.y / (3 * m_winsize.height);
	ele->runAction(MoveTo::create(speed, endPosition));
	// ���뵽spriteSheet��,�ȴ�����
	spritesheet->addChild(ele);

	// ������Ӧλ�ã�������˾����
	map[row][col] = ele;
}


Point PlayLayer::positionOfItem(int row, int col)
{
	float x = mapLBX + (30 + 2) * col + 30 / 2;
	float y = mapLBY + (30 + 2) * row + 30 / 2;

	return Point(x, y);
}


void PlayLayer::update(float dt)
{

	Label* labelscore = (Label*)this->getChildByTag(10);
	labelscore->setString(StringUtils::format("Score: %d", m_score));

	//�����������200��������Ϊ1
	if (m_score >= 200&&mission==1&&finish==false)
	{
		log("suceess");
		Sprite* box = Sprite::create("res/box.png");
		box->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
		this->addChild(box);
		finish = true;
	}
	//�����������������
	if (windtimes >= 2 && mission == 2 && finish == false)
	{
		log("suceess");
		Sprite* box = Sprite::create("res/box.png");
		box->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
		this->addChild(box);
		finish = true;
	}

	//�����������100����û��������һ������
	if (m_score >= 100 && mission == 3 && kuloutimes == 0 && finish == false)
	{
		log("suceess");
		Sprite* box = Sprite::create("res/box.png");
		box->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
		this->addChild(box);
		finish = true;
	}

	if (mission == 3 && kuloutimes >= 1 && finish == false)
	{
		log("suceess");
		Label* end = Label::create("GameOver!!!", "Arial", 100);
		end->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
		this->addChild(end);
		finish = true;
	}

	if (isrun) {

		isrun = false;

		for (int r = 0; r < ROW; ++r)	{
			for (int c = 0; c < COL; ++c)	{
				Element* ele = map[r][c];
				if (ele && ele->getNumberOfRunningActions() > 0) {
					isrun = true;
					break;
				}
			}
		}
	}
	iscantouch = !isrun;


  
	if (!isrun) {

		if (isfiilele) {

			FillEle();
			isfiilele = false;
		}
		else
		{
			checkAndRemoveEle();
		}
	}
}


void PlayLayer::checkAndRemoveEle()
{
	Element *ele;


	for (int r = 0; r < ROW; ++r)	{
		for (int c = 0; c < COL; ++c)	{
			ele = map[r][c];
			if (!ele)	{
				continue;
			}

			ele->setIgnoreCheck(false);
		}
	}



	// ��ͷ����������Ƿ��п��������ľ���
	for (int r = 0; r < ROW; ++r)	{
		for (int c = 0; c < COL; ++c)	{
			ele = map[r][c];
			if (!ele)	{
				continue;
			}



			// ����þ����Ѿ����ӵ� Ҫɾ����List�У�����Ҫ�ټ����
			if (ele->getIsNeedRemove())	{
				continue;
			}
			//����������ɵ�Ԫ��
			if (ele->getIgnoreCheck())
			{
				continue;
			}

			// ����һ��list �洢�ڱ�������Χ�����£��뱾������ͬ�ľ���
			std::list< Element *> colChainList;
			getColChain(ele, colChainList);

			// ����һ��list �洢�ڱ�������Χ�����ң��뱾������ͬ�ľ���
			std::list< Element *> rowChainList;
			getRowChain(ele, rowChainList);

			// ������������list ��ֵ ��longerList
			std::list< Element *> longerList;


			//������ĳ��ȱȺ��Ļ�
			if (colChainList.size() >= rowChainList.size())
			{
				if (colChainList.size() < 3)
				{
					continue;
				}

				longerList = colChainList;
				isrow = false;
			}
			//�����ĳ��ȱ�����Ļ�
			else if (colChainList.size() <= rowChainList.size())
			{
				//���жϣ������ĿС�������Ļ�
				if (rowChainList.size() < 3)
				{
					continue;
				}

				longerList = rowChainList;
				isrow = true;
			}


			std::list<Element*>::iterator itList;
			//��־ �Ƿ���Ҫ�趨���Ӽ��ľ��� 
			bool setIsetedIgnoreCheck = false;
			for (itList = longerList.begin(); itList != longerList.end(); ++itList) {
				ele = (Element*)* itList;
				if (!ele)	{
					continue;
				}
				//���������Ԫ�ش���3
				if (longerList.size() > 3)
				{
					//�����Ԫ�����ڿ�ʼ�������������Ԫ�أ������˱�Ϊ����Ԫ��
					if (ele == staele || ele == endele)
					{
						setIsetedIgnoreCheck = true;
						ele->setIgnoreCheck(true);
						ele->setIsNeedRemove(false);
						//��4������������ɷ�
						ele->setmode(isrow ? wind : dark);
						continue;
					}
				}

				// ���Ҫ�����ľ���
				markRemove(ele);
			}
			//�����Ԫ���Ǻ��Ӽ�鲢��������Ԫ�ش���3
			if (!setIsetedIgnoreCheck&&longerList.size() > 3)
			{
				ele->setIgnoreCheck(true);
				ele->setIsNeedRemove(false);
				ele->setmode(isrow ? wind : dark);
			}

		}
	}

	// ��������˵ľ���
	removeSprite();
}

void PlayLayer::FillEle()
{
	
	int sum = 0;

	isrun = true;

	//����һ��int���͵����飬��ſո��λ��
	int *colemptyinfo = (int*)malloc(sizeof(int)* COL);
	memset((void *)colemptyinfo, 0, sizeof(int)* COL);

	Element* ele = NULL;
	for (int c = 0; c < COL; c++)
	{
		int removedspriteofcol = 0;

		//ÿ�е�һ��ݼ�
		for (int r = 0; r < ROW; r++)
		{
			ele = map[r][c];
			//��������Ԫ�����Ԫ���ǿյĻ������¼��removedspriteofcol
			if (ele == NULL)
			{
				removedspriteofcol++;
			}
			else
			{
				if (removedspriteofcol>0)
				{
					//newrowΪ������Ԫ�ص���һ��
					int newRow = r - removedspriteofcol;
					map[newRow][c] = ele;
					map[r][c] = NULL;

					Point startpos = ele->getPosition();
					Point endpos = positionOfItem(newRow, c);
					float speed = (startpos.y - endpos.y) / m_winsize.height * 3;
					ele->stopAllActions();
					ele->runAction(CCMoveTo::create(speed, endpos));

					ele->setRow(newRow);
				}
			}
		}

		// ��¼��Ӧ�����Ƴ�������  
		colemptyinfo[c] = removedspriteofcol;
		sum += removedspriteofcol;
		
	}

	// �½��µľ��飬������  
	for (int c = 0; c < COL; ++c) {
		for (int r = ROW - colemptyinfo[c]; r < ROW; ++r) {
			createele(r, c);
		}
	}

	m_score += sum * 1;
	free(colemptyinfo);
}

//�������ж���ʲôԪ�أ���ʲô��ʽ����
void PlayLayer::removeSprite()
{
	SimpleAudioEngine::getInstance()->playEffect("music/baozha.mp3", false);

	isrun = true;

	for (int r = 0; r < ROW; ++r)	{
		for (int c = 0; c < COL; ++c)	{
			Element* ele = map[r][c];
			if (!ele)	{
				continue;
			}

			if (ele->getIsNeedRemove())	{
				isfiilele = true;

				//�����Ԫ�ص�ģʽΪ��
				if (ele->getDisplaymode() == wind)
				{
					baozhawind(ele->getPosition());
					
					

				}
				else if (ele->getDisplaymode() == dark)
				{
					;
					

				}
				else if (ele->getDisplaymode() == damage)
				{
					kuloutimes++;
					baozhakulou(ele->getPosition());
				}
				explodeEle(ele);
				
			}
		}
	}
}

void PlayLayer::markRemove(Element* ele)
{
	if (ele->getIsNeedRemove()) {
		return;
	}

	if (ele->getIgnoreCheck())
	{
		return;
	}

	ele->setIsNeedRemove(true);


	// �����Ҫ��ǵ�Ԫ����ʲô���ԣ�����ǵĻ�ִ������Ĳ���
	//�������Ϊȫ������
	if (ele->getDisplaymode() == wind) {

		for (int r = 0; r < ROW; ++r) {
			for (int c = 0; c < COL; ++c)
			{
			
			Element* tmp = map[r][c];
			if (!tmp || tmp == ele) {
				continue;
			}

			if (tmp->getDisplaymode() == normal) {
				tmp->setIsNeedRemove(true);
			}
			else {
				//��������
				markRemove(tmp);
			}
		}
		}
	}
	//�ڰ����������λ�ñ������
	else if (ele->getDisplaymode() == dark) {

		int randnum = (int)(CCRANDOM_0_1() * 10);
		if (randnum < ROW)
		{
			if (map[randnum][ele->getCol()]->getDisplaymode() != damage)
			{
			
			map[randnum][ele->getCol()]->setmode(damage);
			showdamage(map[randnum][ele->getCol()]->getPosition());
			}
		}
		if (randnum < COL)
		{
			if (map[ele->getRow()][randnum]->getDisplaymode() != damage)
			{

				map[ele->getRow()][randnum]->setmode(damage);
				showdamage(map[ele->getRow()][randnum]->getPosition());
			}
		}
	}
	
	else if (ele->getDisplaymode() == damage) {
		//�۷�
		if (m_score-3>=0)
		m_score -= 1;

	}

}

void PlayLayer::getColChain(Element* ele,std::list<Element*> &list)
{
	list.push_back(ele);

	// �������
	int neighborCol = ele->getCol() - 1;
	while (neighborCol >= 0) {
		Element *neighborele = map[ele->getRow()][neighborCol];
		if (neighborele
			&& (neighborele->getImgindex() == ele->getImgindex())
			&& !neighborele->getIsNeedRemove()) {
			list.push_back(neighborele);
			neighborCol--;
		}
		else {
			break;
		}
	}

	// ���Ҳ���
	neighborCol = ele->getCol() + 1;
	while (neighborCol < COL) {
		Element *neighborele = map[ele->getRow()][neighborCol];
		if (neighborele
			&& (neighborele->getImgindex() == ele->getImgindex())
			&& !neighborele->getIsNeedRemove()) {
			list.push_back(neighborele);
			neighborCol++;
		}
		else {
			break;
		}
	}
}

void PlayLayer::getRowChain(Element* ele, std::list<Element*> &list)
{
	list.push_back(ele);

	// ���ϲ���
	int neighborRow = ele->getRow() - 1;
	while (neighborRow >= 0) {
		Element *neighborele = map[neighborRow][ele->getCol()];
		if (neighborele
			&& (neighborele->getImgindex() == ele->getImgindex())
			&& !neighborele->getIsNeedRemove()) {
			list.push_back(neighborele);
			neighborRow--;
		}
		else {
			break;
		}
	}

	// ���²���
	neighborRow = ele->getRow() + 1;
	while (neighborRow < ROW) {
		Element *neighborele = map[neighborRow][ele->getCol()];
		if (neighborele
			&& (neighborele->getImgindex() == ele->getImgindex())
			&& !neighborele->getIsNeedRemove()) {
			list.push_back(neighborele);
			neighborRow++;
		}
		else {
			break;
		}
	}
}


void PlayLayer::explodeEle(Element* ele)
{
	//����ڲ������Ļ������������ö���Ч��ʱ����ֱ�ӷ���
	if (isAnimation) return;


	ele->runAction(Sequence::create(ScaleTo::create(0.2f, 0.0f), CallFuncN::create(CC_CALLBACK_1(PlayLayer::aec, this)), NULL));


	

	//��ըЧ��
	Sprite* yuan = Sprite::create("effect/circle.png");
	if (yuan != NULL)
	{
		yuan->setPosition(ele->getPosition());
		this->addChild(yuan);
		yuan->setScale(0.0f);
		yuan->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, yuan)), NULL));
	}
}

void PlayLayer::aec(Node *node)	{
	Element *ele = (Element *)node;
	map[ele->getRow()][ele->getCol()] = NULL;
	ele->removeFromParent();
}

void PlayLayer::baozhawind(Point point)
{
	Sprite* wind = Sprite::createWithSpriteFrameName("wind1.png");
	//wind->setOpacity(0);
	wind->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
	Vector<SpriteFrame*> vecwind;

	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->playEffect("music/wind.mp3", false);



	for (int i = 1; i <= 6; i++)
	{
		vecwind.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("wind%d.png", i)));
	}

	Animation* animation = Animation::createWithSpriteFrames(vecwind);
	animation->setLoops(5);
	animation->setDelayPerUnit(0.01f);

	Animate* animate = Animate::create(animation);

	auto func = [&](){isAnimation = true; };

	auto func2 = [&](){isAnimation = false; };

	CallFunc* callfunc = CallFunc::create(func);
	CallFunc* callfunc2 = CallFunc::create(func2);

	Sequence* seq = Sequence::create(callfunc, animate, callfunc2, ScaleTo::create(0.1f, 0.0f), NULL);

	wind->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
	this->addChild(wind);
	wind->runAction(seq);

	windtimes++;

}




bool PlayLayer::onTouchbegan(Touch* touch, Event* event)
{
	staele = NULL;
	endele = NULL;

	//����ܴ����Ļ�
	if (iscantouch)
	{

		auto touchpos = touch->getLocation();
		staele = sprofpoint(&touchpos);
	}

	return iscantouch;
}


Element* PlayLayer::sprofpoint(Point* point)
{
	Element* ele = NULL;

	//ģ��һ�����Σ����ݸþ����ж�Ԫ�ص�λ��
	Rect rect = Rect(0, 0, 0, 0);
	Size sz = Size(30, 30);

	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			ele = map[r][c];
			//���spr�Ƿ����
			if (ele)
			{
				//�þ��ε���ʼ������ڸ�Ԫ�ص���ʼ����,����Ԫ�صĴ�С��ֵ���þ���rect 
				rect.origin.x = ele->getPositionX() - (sz.width / 2);
				rect.origin.y = ele->getPositionY() - (sz.height / 2);

				rect.size = sz;

				if (rect.containsPoint(*point))
				{
					return ele;
				}
			}
		}
	}
	return NULL;
}

void PlayLayer::onTouchmoved(Touch* touch, Event* event)
{
	if (!staele || !iscantouch)
	{
		return;
	}


	//��øտ�ʼ�����Ԫ�أ���������������λ��
	int endrow = staele->getRow();
	int endcol = staele->getCol();


	Point touchpos = touch->getLocation();
	auto hwidth = 30 / 2;
	auto hheight = hwidth;

	Rect uprect = Rect(staele->getPositionX() - hwidth, staele->getPositionY() + hwidth, 30, 30);
	Rect downrect = Rect(staele->getPositionX() - hwidth, staele->getPositionY() - hwidth * 3, 30, 30);
	Rect leftrect = Rect(staele->getPositionX() - hwidth * 3, staele->getPositionY() - hwidth, 30, 30);
	Rect rightrect = Rect(staele->getPositionX() + hwidth, staele->getPositionY() - hwidth, 30, 30);

	if (uprect.containsPoint(touchpos))
	{
		if (++endrow < ROW)
		{
			endele = map[endrow][endcol];
			swapspr();
			return;
		}

	}

	if (downrect.containsPoint(touchpos))
	{
		if (--endrow >= 0)
		{
			endele = map[endrow][endcol];
			swapspr();
			return;
		}
	}

	if (leftrect.containsPoint(touchpos))
	{
		if (--endcol >= 0)
		{
			endele = map[endrow][endcol];
			swapspr();
			return;
		}
	}

	if (rightrect.containsPoint(touchpos))
	{
		if (++endcol < COL)
		{
			endele = map[endrow][endcol];
			swapspr();
			return;
		}
	}
}

void PlayLayer::swapspr()
{
	//�����в�������
	iscantouch = false;
	isrun = true;

	if (!staele || !endele)
	{
		return;
	}

	Point startpos = staele->getPosition();
	Point endpos = endele->getPosition();

	//Ԫ�ص�������map�ｻ��
	map[staele->getRow()][staele->getCol()] = endele;
	map[endele->getRow()][endele->getCol()] = staele;

	int tmprow = staele->getRow();
	int tmpcol = staele->getCol();
	staele->setRow(endele->getRow());
	staele->setCol(endele->getCol());
	endele->setCol(tmpcol);
	endele->setRow(tmprow);

	//�����ݽ�����󣬼�����������Ƿ��������
	std::list<Element*> startcolcollist;
	getColChain(staele, startcolcollist);

	std::list<Element*> startrowcollist;
	getRowChain(staele, startrowcollist);

	std::list<Element*> endcollist;
	getColChain(endele, endcollist);

	std::list<Element*> endrowlist;
	getRowChain(endele, endrowlist);

	if (startcolcollist.size() >= 3 || startrowcollist.size() >= 3 || endcollist.size() >= 3 || endrowlist.size() >= 3)
	{

		staele->runAction(MoveTo::create(0.2f, endpos));
		endele->runAction(MoveTo::create(0.2f, startpos));
	}
	else
	{
		map[endele->getRow()][endele->getCol()] = staele;
		map[staele->getRow()][staele->getCol()] = endele;

		int tmprow = staele->getRow();
		int tmpcol = staele->getCol();
		staele->setRow(endele->getRow());
		staele->setCol(endele->getCol());
		endele->setCol(tmpcol);
		endele->setRow(tmprow);

		staele->runAction(Sequence::create(MoveTo::create(0.2f, endpos), MoveTo::create(0.2f, startpos), NULL));
		endele->runAction(Sequence::create(MoveTo::create(0.2f, startpos), MoveTo::create(0.2f, endpos), NULL));
	}


}

//�ڰ��򱬷���ʱ�򴥷���
void PlayLayer::showdamage(Point point)
{
	Sprite* kulou = Sprite::createWithSpriteFrameName("kulou.png");
	kulou->setPosition(point);
	this->addChild(kulou);
	kulou->setScale(0.0f);
	kulou->runAction(Sequence::create(ScaleTo::create(0.2f, 3.0f), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, kulou)), NULL));
}

//��������Ԫ��֮��������Ч
void PlayLayer::baozhakulou(Point point)
{
	Sprite* head = Sprite::createWithSpriteFrameName("head1.png");
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->playEffect("music/baozhakulou.mp3", false);

	Vector<SpriteFrame*> vecwind;



	for (int i = 1; i <= 7; i++)
	{
		vecwind.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("head%d.png", i)));
	}

	Animation* animation = Animation::createWithSpriteFrames(vecwind);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	Animate* animate = Animate::create(animation);

	auto func = [&](){isAnimation = true; };

	auto func2 = [&](){isAnimation = false; };

	CallFunc* callfunc = CallFunc::create(func);
	CallFunc* callfunc2 = CallFunc::create(func2);

	Sequence* seq = Sequence::create(callfunc,Spawn::create(ScaleTo::create(0.3f,3.0f),animate,FadeOut::create(0.3f)), callfunc2,  NULL);

	head->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
	this->addChild(head);
	head->runAction(seq);
}

void PlayLayer::setpause(Ref* obj)
{
	pause();
	
}

void PlayLayer::setresume(Ref* obj)
{
	resume();

}

void PlayLayer::setuseaddwind(Ref* obj)
{
	Element* ele;

	

	while (true)
	{
		int randnum = (int)(rand()% 10);
	if (randnum < ROW&&randnum < COL)
	{
		ele = map[randnum][randnum];
		if (ele->getDisplaymode() == wind) continue;
		else
		ele->setmode(wind);
		break;
	}
	else
	{
		continue;
	}
	}
	Sprite* yuan = Sprite::create("effect/circle.png");
	if (yuan != NULL)
	{
		yuan->setPosition(ele->getPosition());
		this->addChild(yuan);
		yuan->setScale(0.0f);
		yuan->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, yuan)), NULL));
	}
}

void PlayLayer::setusekulouitem(Ref* obj)
{
	Element* ele;

	for (int r = 0; r < ROW; r++)
	{
		for (int c = 0; c < COL; c++)
		{
			ele = map[r][c];
			if (ele->getDisplaymode() == damage)
			{
				ele->setmode(normal);

				Sprite* yuan = Sprite::create("effect/circle.png");
				if (yuan != NULL)
				{
					yuan->setPosition(ele->getPosition());
					this->addChild(yuan);
					yuan->setScale(0.0f);
					yuan->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, yuan)), NULL));
				}
			}
		}
	}

}

void PlayLayer::setuseclearall(Ref* obj)
{

	baozhawind(Point::ZERO);
	for (int r = 0; r < ROW; ++r) {
		for (int c = 0; c < COL; ++c)
		{

			Element* tmp = map[r][c];
		
				markRemove(tmp);
			}
		}
	removeSprite();

}


//������1
void PlayLayer::mission1(Ref* obj)
{
	
	mission = 1;

}

//������2
void PlayLayer::mission2(Ref* obj)
{

	mission = 2;

}

//������3
void PlayLayer::mission3(Ref* obj)
{
	
	mission = 3;


	
}

