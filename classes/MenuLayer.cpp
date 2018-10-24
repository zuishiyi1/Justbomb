#include "MenuLayer.h"
#include "GameScene.h"

MenuLayer::MenuLayer()
{
	sound = true;
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/Imagine Dragons - Demons.mp3", true);
}

MenuLayer::~MenuLayer()
{

}

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	m_winsize = size;
	
	addTouch();
	addTitle();

	//创建说明背景
	Sprite* shuomingbg = Sprite::create("background/shuomingbg.png");
	shuomingbg->setTag(50);
	shuomingbg->setVisible(false);
	shuomingbg->setScaleY(1.1f);
	shuomingbg->setScaleX(1.2f);
	shuomingbg->setPosition(Point(m_winsize.width / 2+10, m_winsize.height / 2));
	this->addChild(shuomingbg);


	Sprite* shuomingtext = Sprite::create("background/shuomingtext.png");
	shuomingtext->setTag(51);
	shuomingtext->setVisible(false);
	shuomingtext->setScaleY(0.6f);
	shuomingtext->setScaleX(0.6f);
	shuomingtext->setPosition(Point(m_winsize.width / 2+10, m_winsize.height / 2));
	this->addChild(shuomingtext);

	return true;
}

//添加标题
void MenuLayer::addTitle()
{



	//添加标题
	title = Sprite::create("title/title.png");
	this->addChild(title);
	title->setPosition(Point(m_winsize.width / 2, m_winsize.height + title->getContentSize().height));

	//移动标题
	auto movetotitle = MoveTo::create(0.5, Point(m_winsize.width / 2, m_winsize.height - title->getContentSize().height));
	

	CallFunc* callstartbtn = CallFunc::create(this, callfunc_selector(MenuLayer::addStartBtn));

	Sequence* seq = Sequence::create(movetotitle, callstartbtn,NULL);
	title->runAction(seq);

	

	

	

}

//添加开始游戏按钮
void MenuLayer::addStartBtn()
{
	//把开始游戏按钮文件添加到framcache
	SpriteFrameCache* framecache = SpriteFrameCache::getInstance();
	framecache->addSpriteFramesWithFile("button/startgame.plist", "button/startgame.png");

	//创建开始游戏按钮
	kaibtn = Sprite::createWithSpriteFrameName("kai.png");
	kaibtn->setPosition(Point(m_winsize.width / 4, -kaibtn->getContentSize().height));
	this->addChild(kaibtn);

	shibtn = Sprite::createWithSpriteFrameName("shi.png");
	shibtn->setPosition(Point(m_winsize.width / 4 + shibtn->getContentSize().width, -shibtn->getContentSize().height));
	this->addChild(shibtn);

	youbtn = Sprite::createWithSpriteFrameName("you.png");
	youbtn->setPosition(Point(m_winsize.width / 4 + shibtn->getContentSize().width+youbtn->getContentSize().width, -youbtn->getContentSize().height));
	this->addChild(youbtn);

	xibtn = Sprite::createWithSpriteFrameName("xi.png");
	xibtn->setPosition(Point(m_winsize.width / 4 + shibtn->getContentSize().width + youbtn->getContentSize().width + xibtn->getContentSize().width, -xibtn->getContentSize().height));
	this->addChild(xibtn);


	shuoming = Sprite::create("button/shuoming.png");
	shuoming->setPosition(Point(shuoming->getContentSize().width/2, shuoming->getContentSize().height*2));
	this->addChild(shuoming);

	Sprite* sound = Sprite::create("button/soundon.png");
	sound->setPosition(Point(m_winsize.width - sound->getContentSize().width / 2, m_winsize.height - sound->getContentSize().height / 2));
	sound->setTag(100);
	this->addChild(sound);
	

	auto movekai = MoveBy::create(0.5, Point(0, kaibtn->getContentSize().height + kaibtn->getContentSize().height/2));
	auto moveshi = MoveBy::create(0.5, Point(0, shibtn->getContentSize().height + shibtn->getContentSize().height / 2));
	auto moveyou = MoveBy::create(0.5, Point(0, youbtn->getContentSize().height + youbtn->getContentSize().height / 2));
	auto movexi = MoveBy::create(0.5, Point(0, xibtn->getContentSize().height + xibtn->getContentSize().height / 2));
	kaibtn->runAction(movekai);
	shibtn->runAction(moveshi);
	youbtn->runAction(moveyou);
	xibtn->runAction(movexi);


	

	


}

void MenuLayer::addTouch()
{
	EventListenerTouchOneByOne* listener;

	listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		if (kaibtn->boundingBox().containsPoint(pos)){
			SimpleAudioEngine::getInstance()->playEffect("music/startgame.mp3", false);
			kaibtn->setTexture("res/kai2.png");
		}

		if (shibtn->boundingBox().containsPoint(pos)){
			SimpleAudioEngine::getInstance()->playEffect("music/startgame.mp3", false);
			shibtn->setTexture("res/shi2.png");
		}

		if (youbtn->boundingBox().containsPoint(pos)){
			SimpleAudioEngine::getInstance()->playEffect("music/startgame.mp3", false);
			youbtn->setTexture("res/you2.png");
		}

		if (xibtn->boundingBox().containsPoint(pos)){
			SimpleAudioEngine::getInstance()->playEffect("music/startgame.mp3", false);
			xibtn->setTexture("res/xi2.png");
		}

		if (shuoming->boundingBox().containsPoint(pos)){
			SimpleAudioEngine::getInstance()->playEffect("music/startgame.mp3", false);
			shuoming->setTexture("button/shuoming2.png"); }

		if (this->getChildByTag(100)->boundingBox().containsPoint(pos))
		{
			auto sp = (Sprite*)this->getChildByTag(100);
			if (sound == true)
			{
				sp->setTexture("button/soundclose.png");
				SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
				sound = false;
			}
			
			else
			{
				sp->setTexture("button/soundon.png");
				SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
				sound = true;
			}
		}
			

		return true;
	};

	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		if (kaibtn->boundingBox().containsPoint(pos) || shibtn->boundingBox().containsPoint(pos) || youbtn->boundingBox().containsPoint(pos) || xibtn->boundingBox().containsPoint(pos))
		{

			

			kaibtn->setTexture("res/kai.png");
			shibtn->setTexture("res/shi.png");
			youbtn->setTexture("res/you.png");
			xibtn->setTexture("res/xi.png");

			auto titlemoveby = MoveBy::create(0.5f, Point(0, 250));
			auto movekai = MoveBy::create(0.5, Point(0, -kaibtn->getContentSize().height));
			auto moveshi = MoveBy::create(0.5, Point(0, -shibtn->getContentSize().height));
			auto moveyou = MoveBy::create(0.5, Point(0, -youbtn->getContentSize().height));
			auto movexi = MoveBy::create(0.5, Point(0, -xibtn->getContentSize().height));

			
			kaibtn->runAction(movekai);
			shibtn->runAction(moveshi);
			youbtn->runAction(moveyou);
			xibtn->runAction(movexi);

			

			auto nextscene = [&](){Director::getInstance()->replaceScene(TransitionSlideInB::create(0.5f, GameScene::createscene())); SimpleAudioEngine::getInstance()->stopBackgroundMusic(); };
			CallFunc* callnextscene = CallFunc::create(nextscene);
			auto seq = Sequence::create(titlemoveby, callnextscene, NULL);
			title->runAction(seq);
			
		}
		if (shuoming->boundingBox().containsPoint(pos))
		{
			this->getChildByTag(50)->setVisible(true);
			this->getChildByTag(51)->setVisible(true);
			shuoming->setTexture("button/shuoming.png");
			return;
			
		}
		this->getChildByTag(50)->setVisible(false);
		this->getChildByTag(51)->setVisible(false);

	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}