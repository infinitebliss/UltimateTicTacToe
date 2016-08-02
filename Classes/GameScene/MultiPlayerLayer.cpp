//
//  MultiPlayerLayer.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "MultiPlayerLayer.hpp"

#include "Board.hpp"
#include "Block.hpp"
#include "GameOverLayer.hpp"

#include "ui/CocosGUI.h"

USING_NS_CC;

MultiPlayerLayer::MultiPlayerLayer()
{
    _player = Block::Player::PLAYER1;
    _gameState = GameState::PLAYING;
}

MultiPlayerLayer::~MultiPlayerLayer()
{
    
}

bool MultiPlayerLayer::init()
{
    if(!Layer::init()) return false;
    
    // size of window
    Size winSize = Director::getInstance()->getWinSize();
    
    // player player now
    _playerNow = Sprite::create("player1.png");
    _playerNow->setPosition(Vec2(winSize.width / 2.0, winSize.height - 375));
    this->addChild(_playerNow);
    
    // place undo button
    _undo = cocos2d::ui::Button::create("undo.png", "undo_pressed.png", "undo_pressed.png");
    _undo->setPosition(Vec2(winSize.width / 2.0, 175));
    _undo->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
            {
                if(_player == Block::Player::PLAYER1) {
                    _player = Block::Player::PLAYER2;
                    _playerNow->setTexture("player2.png");
                    
                }
                else if(_player == Block::Player::PLAYER2){
                    _player = Block::Player::PLAYER1;
                    _playerNow->setTexture("player1.png");
                }
                _board->undoMove(_player);
                _undo->setBright(false);
                break;
            }
            default:
                break;
        }
    });
    this->addChild(_undo);
    _undo->setBright(false);

    // place board
    _board = Board::create();
    _board->setPosition(Vec2(winSize.width / 2.0, _board->getContentSize().height / 2.0 + 200));
    this->addChild(_board);
    
    // touch event
    auto listener = EventListenerTouchOneByOne::create();
    // user began touching
    listener->onTouchBegan = [this](Touch* touch, Event* event){
        // call on touch began function
        onTouchBegan(touch);
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

       
    return true;
}

void MultiPlayerLayer::onTouchBegan(Touch *touch)
{
    Vec2 touchBegan = touch->getLocation();
    // place block
    // if user touches within the board
    if(_board->getBoundingBox().containsPoint(touchBegan)){
        if(_board->makeMoveFromTouch(touch, _player))
        {
            _undo->setBright(true);
            if(_board->checkWin())
            {
                gameDone();
                _gameState = GameState::PLAYING;
            }
            else if(_board->checkDraw())
            {
                _player = Block::Player::NEITHER;
                gameDone();
                _gameState = GameState::DONE;
            }
            else{
                if(_player == Block::Player::PLAYER1)
                {
                    // set next player
                    _player = Block::Player::PLAYER2;
                    _playerNow->setTexture("player2.png");
                }
                else if(_player == Block::Player::PLAYER2)
                {
                    // set next player
                    _player = Block::Player::PLAYER1;
                    _playerNow->setTexture("player1.png");
                }
            }
        }
    }
}

void MultiPlayerLayer::gameDone()
{
    Size winSize = Director::getInstance()->getWinSize();
    GameOverLayer* gameoverlayer = GameOverLayer::create(_player);
    gameoverlayer->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(gameoverlayer);
}