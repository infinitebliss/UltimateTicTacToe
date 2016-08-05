//
//  LevelScene.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-03.
//
//

#include "LevelScene.hpp"

#include "TitleScene.hpp"
#include "GameScene.hpp"

USING_NS_CC;

LevelScene::LevelScene()
{
    
}

LevelScene::~LevelScene()
{
    
}

Scene* LevelScene::createScene()
{
    Scene* scene = Scene::create();
    LevelScene* layer = LevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init()
{
    if(!Layer::init()) return false;
    
    // window size
    Size winSize = Director::getInstance()->getWinSize();
    
    // user default
    UserDefault* ud = UserDefault::getInstance();
    
    // place background
    Sprite* background = Sprite::create("bg_white.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    // place logo
    Sprite* logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(winSize.width / 2.0, winSize.height - 250));
    this->addChild(logo);
    
    // place menu button
    cocos2d::ui::Button* menu = cocos2d::ui::Button::create("menu.png", "menu_pressed.png");
    menu->setPosition(Vec2(menu->getContentSize().width / 2.0 + 50, winSize.height - menu->getContentSize().height / 2.0 - 50));
    menu->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                CCLOG("menu");
                // start game
                Scene* scene = TitleScene::createScene();
                TransitionSlideInT* transition = TransitionSlideInT::create(1.0, scene);
                Director::getInstance()->replaceScene(transition);
                break;
            }
            default:
                break;
        }
    });
    this->addChild(menu);
    
    // place ad banner
    Sprite* ad = Sprite::create("ad.png");
    ad->setPosition(Vec2(winSize.width / 2.0, ad->getContentSize().height / 2.0));
    this->addChild(ad);
    
    // level selection
    // easy mode
    MenuItemImage* easy = MenuItemImage::create("easy.png", "easy.png", [&](Ref* ref){
        // make sure they cant press twice
        this->getEventDispatcher()->removeAllEventListeners();
        // save to user default so when transitioned to game scene know which layer to load
        UserDefault::getInstance()->setStringForKey("mode", "easy");
        UserDefault::getInstance()->flush();
        // start game
        Scene* scene = GameScene::createScene();
        TransitionSlideInB* transition = TransitionSlideInB::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    // medium mode
    MenuItemImage* medium = MenuItemImage::create("medium.png", "medium.png", [&](Ref* ref){
        // make sure they cant press twice
        this->getEventDispatcher()->removeAllEventListeners();
        // save to user default so when transitioned to game scene know which layer to load
        UserDefault::getInstance()->setStringForKey("mode", "medium");
        UserDefault::getInstance()->flush();
        // start game
        std::string str = UserDefault::getInstance()->getStringForKey("mode");
        CCLOG("Mode: %s", str.c_str());
        Scene* scene = GameScene::createScene();
        TransitionSlideInB* transition = TransitionSlideInB::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    // hard mode
    MenuItemImage* hard = MenuItemImage::create("hard.png", "hard.png", [&](Ref* ref){
        // make sure they cant press twice
        this->getEventDispatcher()->removeAllEventListeners();
        // save to user default so when transitioned to game scene know which layer to load
        UserDefault::getInstance()->setStringForKey("mode", "hard");
        UserDefault::getInstance()->flush();
        // start game
        Scene* scene = GameScene::createScene();
        TransitionSlideInB* transition = TransitionSlideInB::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    // extreme mode
    MenuItemImage* extreme = MenuItemImage::create("extreme.png", "extreme.png", [&](Ref* ref){
        // make sure they cant press twice
        this->getEventDispatcher()->removeAllEventListeners();
        // save to user default so when transitioned to game scene know which layer to load
        UserDefault::getInstance()->setStringForKey("mode", "extreme");
        UserDefault::getInstance()->flush();
        // start game
        Scene* scene = GameScene::createScene();
        TransitionSlideInB* transition = TransitionSlideInB::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    // create menu
    Menu* levelmenu = Menu::create(easy, medium, hard, extreme, NULL);
    levelmenu->alignItemsVerticallyWithPadding(50);
    levelmenu->setPosition(Vec2(winSize.width / 2.0, winSize.height - 700));
    levelmenu->setAnchorPoint(Vec2(0.5, 1));
    this->addChild(levelmenu);


    return true;
}
