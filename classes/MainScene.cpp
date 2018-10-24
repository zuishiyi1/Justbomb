#include "MainScene.h"
#include "MenuLayer.h"
#include "Cell.h"
Scene* MainScene::createScene()
{
	//auto scene = Scene::create();

	/*auto layer = MainScene::create();

	scene->addChild(layer);

	MenuLayer* menulayer = MenuLayer::create();

	scene->addChild(menulayer);*/

	

	//return scene;

	return MainScene::create();
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;

	}

	//获取窗口可见大小
	Size winsize = Director::getInstance()->getVisibleSize();

	//添加背景图片
	Sprite* bg = Sprite::create("background/MainScene.png");
	if (bg != NULL)
	{
		this->addChild(bg);
		bg->setPosition(Point(winsize.width / 2, winsize.height / 2));
	}

	//如果是第一次运行这程序
	if (UserDefault::getInstance()->getBoolForKey("firstrun", true))
	{
		UserDefault::getInstance()->setBoolForKey("firstrun",false);

		UserDefault::getInstance()->setIntegerForKey("itemnum-addwind", 10);

		UserDefault::getInstance()->setIntegerForKey("itemnum-clearall", 10);

		UserDefault::getInstance()->setIntegerForKey("itemnum-kulouitem", 10);

		UserDefault::getInstance()->flush();
	}

	MenuLayer* menulayer = MenuLayer::create();

	this->addChild(menulayer);



	//addEffect();
	
	

	return true;
}

void MainScene::addEffect()
{

	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("particle_texture.plist");
	m_emitter1->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(m_emitter1->getTexture());
	batch->addChild(m_emitter1);
	addChild(batch, 10);
	m_emitter1->release();
}

void MainScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}