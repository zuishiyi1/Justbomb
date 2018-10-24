#include "Package.h"
#include "MainScene.h"

#define BOADER 13

#define CELL_WIDTH 45

bool Package::init()
{
	if (!Layer::init()) return false;

	m_winsize = Director::getInstance()->getVisibleSize();

	addwinditem=NULL;

	kulouitem = NULL;

	clearallitem = NULL;


	packageitem = MenuItemImage::create("background/Package.png", "background/Packageon.png", "background/Packagedisabled.png", this, menu_selector(Package::openPackage));
	packageitem->setPosition(Point(m_winsize.width - packageitem->getContentSize().width / 4, packageitem->getContentSize().height / 4));
	packageitem->setScale(0.3f);

	
	menu = Menu::create(packageitem, NULL);
	menu->setTag(20);
	menu->setLocalZOrder(2);
	menu->setContentSize(m_winsize);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Package::ontouchbegan,this);
	listener->setSwallowTouches(true);
	listener->setEnabled(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	

	addwindnum = UserDefault::getInstance()->getIntegerForKey("itemnum-addwind");

	kulouitemnum = UserDefault::getInstance()->getIntegerForKey("itemnum-kulouitem");

	clearallnum = UserDefault::getInstance()->getIntegerForKey("itemnum-clearall");
	

	return true;
}

void Package::openPackage(Ref* pSender)
{
	listener->setEnabled(true);
	packageitem->setEnabled(false);

	Sprite* bgblack = Sprite::create("background/black.png");
	bgblack->setTag(1);
	bgblack->setLocalZOrder(1);
	this->addChild(bgblack);
	bgblack->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));

	pk = Sprite::create("background/pk.png");
	pk->setTag(2);
	pk->setLocalZOrder(1);
	this->addChild(pk);
	pk->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
	pk->setScaleX(0.7f);
	pk->setScaleY(0.8f);

	inititem();

	auto closebtn = MenuItemImage::create("background/closepknormal.png", "background/closepk.png", this, menu_selector(Package::closePackage));
	closebtn->setPosition(Point(pk->getContentSize().width-closebtn->getContentSize().width/4,pk->getContentSize().height-closebtn->getContentSize().height/4));
	menu->addChild(closebtn);

	NotificationCenter::getInstance()->postNotification(StringUtils::toString(openpk));

}

void Package::closePackage(Ref* pSender)
{
	
}

bool Package::ontouchbegan(Touch* _touch, Event* _event)
{
	if (!pk->boundingBox().containsPoint(_touch->getLocation()))
	{
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(closepk));
		if (kulouitem != NULL)
			kulouitem->setVisible(false);
		if (clearallitem != NULL)
			clearallitem->setVisible(false);
		if (addwinditem != NULL)
			addwinditem->setVisible(false);
		this->removeChildByTag(1);
		this->removeChildByTag(2);
		this->removeChildByTag(3);
		this->removeChildByTag(4);
		this->removeChildByTag(5);
		this->removeChildByTag(6);
		this->removeChildByTag(6);
		listener->setEnabled(false);
		packageitem->setEnabled(true);


		return true;


	}

	

	return true;
}


void Package::inititem()
{
	if (addwindnum > 0)
	{
		addwinditem = MenuItemImage::create("element/addwind.png", "element/addwind1.png", this, menu_selector(Package::useaddwind));
		addwinditem->setTag(3);
		addwinditem->setPosition(Point(addwinditem->getContentSize().width + 5, pk->getContentSize().height - addwinditem->getContentSize().height*1.5));
		menu->addChild(addwinditem);

		

		//数量的创建
		auto label = Label::create(StringUtils::format("%d", addwindnum), "Arial", 10);
		label->setLocalZOrder(2);
		this->addChild(label);
		label->setTag(4);
		label->setPosition(Point(CELL_WIDTH + CELL_WIDTH / 2, pk->getContentSize().height - CELL_WIDTH*1.5 - 20));
	}
	else if (addwinditem!=NULL)
	{
		addwinditem->setVisible(false);
	}

	if (kulouitemnum > 0)
	{
		kulouitem = MenuItemImage::create("element/kulouitem.png", "element/kulouitem.png", this, menu_selector(Package::usekulouitem));
		kulouitem->setTag(5);
		kulouitem->setPosition(Point(CELL_WIDTH + 5+BOADER+kulouitem->getContentSize().width, pk->getContentSize().height - CELL_WIDTH*1.5));
		menu->addChild(kulouitem);



		//数量的创建
		auto label2 = Label::create(StringUtils::format("%d", kulouitemnum), "Arial", 10);
		label2->setLocalZOrder(2);
		this->addChild(label2);
		label2->setTag(6);
		label2->setPosition(Point(CELL_WIDTH + CELL_WIDTH / 2 + BOADER + kulouitem->getContentSize().width, pk->getContentSize().height - CELL_WIDTH*1.5 - 20));
	}
	else if (kulouitem != NULL)
	{
		kulouitem->setVisible(false);
	}

	
	if (clearallnum > 0)
	{
		clearallitem = MenuItemImage::create("element/clearall.png", "element/clearall.png", this, menu_selector(Package::useclearall));
		clearallitem->setTag(7);
		clearallitem->setPosition(Point(CELL_WIDTH * 2 + 10 + BOADER+clearallitem->getContentSize().width/2, pk->getContentSize().height - CELL_WIDTH*1.5));
		menu->addChild(clearallitem);



		//数量的创建
		auto label2 = Label::create(StringUtils::format("%d", clearallnum), "Arial", 10);
		label2->setLocalZOrder(2);
		this->addChild(label2);
		label2->setTag(8);
		label2->setPosition(Point(CELL_WIDTH + CELL_WIDTH / 2 + CELL_WIDTH / 2 + BOADER*1.5 + clearallitem->getContentSize().width, pk->getContentSize().height - CELL_WIDTH*1.5 - 20));
	}
	else if (clearallitem != NULL)
	{
		clearallitem->setVisible(false);
	}

	

}


void Package::useaddwind(Ref* pSender)
{

	//获取数量的label
	auto label = (Label*)this->getChildByTag(4);
	addwindnum--;
	if (addwindnum <= 0)
	{
		UserDefault::getInstance()->setIntegerForKey("itemnum-addwind", addwindnum);
		UserDefault::getInstance()->flush();
		addwinditem->setVisible(false);
		if (kulouitem!=NULL)
		kulouitem->setVisible(false);
		if (clearallitem != NULL)
			clearallitem->setVisible(false);
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(closepk));
		this->removeChildByTag(1);
		this->removeChildByTag(2);
		this->removeChildByTag(4);
		this->removeChildByTag(5);
		this->removeChildByTag(6);
		this->removeChildByTag(8);
		listener->setEnabled(false);
		packageitem->setEnabled(true);
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(state_useaddwinditem));

		return;
	}
	
	UserDefault::getInstance()->setIntegerForKey("itemnum-addwind", addwindnum);
	UserDefault::getInstance()->flush();
	label->setString(StringUtils::format("%d", addwindnum));

	NotificationCenter::getInstance()->postNotification(StringUtils::toString(state_useaddwinditem));
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(closepk));
	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(4);
	this->removeChildByTag(5);
	this->removeChildByTag(6);
	this->removeChildByTag(8);
	addwinditem->setVisible(false);
	if (kulouitem != NULL)
	kulouitem->setVisible(false);
	if (clearallitem != NULL)
		clearallitem->setVisible(false);
	listener->setEnabled(false);
	packageitem->setEnabled(true);

	
}


void Package::usekulouitem(Ref* pSender)
{
	//获取数量的label
	auto label = (Label*)this->getChildByTag(6);
	kulouitemnum--;
	if (kulouitemnum <= 0)
	{
		UserDefault::getInstance()->setIntegerForKey("itemnum-kulouitem", kulouitemnum);
		UserDefault::getInstance()->flush();
		kulouitem->setVisible(false);
		if (addwinditem!=NULL)
		addwinditem->setVisible(false);
		if (clearallitem != NULL)
			clearallitem->setVisible(false);
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(state_usekulouitem));
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(closepk));
		this->removeChildByTag(1);
		this->removeChildByTag(2);
		this->removeChildByTag(4);
		this->removeChildByTag(5);
		this->removeChildByTag(6);
		this->removeChildByTag(8);
		listener->setEnabled(false);
		packageitem->setEnabled(true);


		return;
	}

	UserDefault::getInstance()->setIntegerForKey("itemnum-kulouitem", kulouitemnum);
	UserDefault::getInstance()->flush();
	label->setString(StringUtils::format("%d", kulouitemnum));
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(state_usekulouitem));
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(closepk));
	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(4);
	this->removeChildByTag(5);
	this->removeChildByTag(6);
	this->removeChildByTag(8);
	kulouitem->setVisible(false);
	if (addwinditem != NULL)
	addwinditem->setVisible(false);
	if (clearallitem != NULL)
		clearallitem->setVisible(false);
	listener->setEnabled(false);
	packageitem->setEnabled(true);
}


void Package::useclearall(Ref* pSender)
{
	//获取数量的label
	auto label = (Label*)this->getChildByTag(8);
	clearallnum--;
	if (clearallnum <= 0)
	{
		UserDefault::getInstance()->setIntegerForKey("itemnum-clearall", clearallnum);
		UserDefault::getInstance()->flush();
		clearallitem->setVisible(false);
		if (addwinditem != NULL)
			addwinditem->setVisible(false);
		if (kulouitem != NULL)
			kulouitem->setVisible(false);
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(state_useclearallitem));
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(closepk));
		this->removeChildByTag(1);
		this->removeChildByTag(2);
		this->removeChildByTag(4);
		this->removeChildByTag(5);
		this->removeChildByTag(6);
		this->removeChildByTag(7);
		this->removeChildByTag(8);
		listener->setEnabled(false);
		packageitem->setEnabled(true);


		return;
	}

	UserDefault::getInstance()->setIntegerForKey("itemnum-clearall", clearallnum);
	UserDefault::getInstance()->flush();
	label->setString(StringUtils::format("%d", clearallnum));
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(state_useclearallitem));
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(closepk));
	this->removeChildByTag(1);
	this->removeChildByTag(2);
	this->removeChildByTag(4);
	this->removeChildByTag(5);
	this->removeChildByTag(6);
	this->removeChildByTag(8);
	this->removeChildByTag(7);
	clearallitem->setVisible(false);
	if (addwinditem != NULL)
		addwinditem->setVisible(false);
	if (kulouitem != NULL)
		kulouitem->setVisible(false);
	listener->setEnabled(false);
	packageitem->setEnabled(true);
}



