#include "GameScene.h"
#include "Cell.h"
#include "PlayLayer.h"
#include "Package.h"
Scene* GameScene::createscene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer,1);


	auto cell = Cell::create();
	scene->addChild(cell,2);

	auto playlayer = PlayLayer::create();
	scene->addChild(playlayer,3);

	

	auto package = Package::create();
	scene->addChild(package,4);
	

	return scene;

}



bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_winsize  = Director::getInstance()->getVisibleSize();
	
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::mission1), StringUtils::toString(scoredayuerbai), NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::mission2), StringUtils::toString(wanchengliangcicixuanfeng), NULL);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayLayer::mission3), StringUtils::toString(scoredayuyibaibingbunengyicikulou), NULL);

	Sprite* bg = Sprite::create("background/GameScene.png");

	this->addChild(bg);
	bg->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));

	Sprite* conditionbg = Sprite::create("background/conditionbg.png");
	conditionbg->setScale(0.7f);
	conditionbg->setPosition(Point(m_winsize.width / 2, m_winsize.height / 2));
	this->addChild(conditionbg);
	conditionbg->runAction(Sequence::create(DelayTime::create(0.5f), MoveBy::create(0.5f, Point(0, -200)),NULL));

	int i = rand() % 3;
	log("mission: %d", i);
	if (i == 0)
	{
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(scoredayuerbai));
	}
	if (i == 1)
	{
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(wanchengliangcicixuanfeng));
	}
	if (i == 2)
	{
		NotificationCenter::getInstance()->postNotification(StringUtils::toString(scoredayuyibaibingbunengyicikulou));
	}
	condition = Sprite::create(StringUtils::format("res/condition%d.png",i));
	condition->setPosition(conditionbg->getPosition());
	condition->setOpacity(255);
	condition->setScale(0.7f);
	this->addChild(condition);
	

	condition->runAction(Sequence::create(DelayTime::create(0.5f), MoveBy::create(0.5f, Point(0, -200)),NULL));
	

	return true;
}


