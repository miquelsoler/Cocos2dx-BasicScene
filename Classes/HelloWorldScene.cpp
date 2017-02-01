#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getVisibleSize();

    // Draw Nintendo-like sky
    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, Color4F(0.2, 0.5, 0.95, 1.0));
    this->addChild(background);

    // Add Mario as a sprite
    _player = Sprite::create("mario.png");
    _player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
    this->addChild(_player);

    // Add enemies
    srand((unsigned int)time(nullptr));
    this->schedule(schedule_selector(HelloWorld::addEnemy), 1.5);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
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

void HelloWorld::addEnemy(float dt)
{
    // Crea l'sprite de l'enemic i posiciona'l

    auto enemy = Sprite::create("enemy.png");

    auto enemyContentSize = enemy->getContentSize(); // Tamany de l'sprite enemic
    auto selfContentSize = this->getContentSize(); // Tamany de la finestra

    int minY = enemyContentSize.height/2; // La Y mínima de l'enemic és la seva alçada/2, per a que no apareixi partit
    int maxY = selfContentSize.height - enemyContentSize.height/2; // Ídem per a la Y màxima

    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY; // Li donem a l'enemic una Y aleatòria, però vàlida

    enemy->setPosition(Vec2(selfContentSize.width + enemyContentSize.width + enemyContentSize.width/2, randomY));
    this->addChild(enemy); // Afegim l'enemic a l'escena

    // Crea una acció per a l'enemic

    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    // Acció de moviment
    auto actionMove = MoveTo::create(randomDuration, Vec2(-enemyContentSize.width/2, randomY));

    // Acció d'eliminar-se un cop desapareix
    auto actionRemove = RemoveSelf::create();

    // Crea seqüència d'accions: mou i esborra't quan hagis acabat de moure't
    enemy->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}
