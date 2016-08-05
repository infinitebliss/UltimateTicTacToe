//
//  SinglePlayerLayer.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-07-29.
//
//

#include "SinglePlayerLayer.hpp"

#include "GameOverLayer.hpp"


USING_NS_CC;

SinglePlayerLayer::SinglePlayerLayer()
{
    
}

SinglePlayerLayer::~SinglePlayerLayer()
{
    
}

bool SinglePlayerLayer::init()
{
    if(!Layer::init()) return false;
    
    Size winSize = Director::getInstance()->getWinSize();
    
    _bots = Bots::create();
    
    // player set up
    _player = Block::Player::PLAYER1;
    _playerNow = Sprite::create("yourturn.png");
    _playerNow->setPosition(Vec2(winSize.width / 2.0, winSize.height - 375));
    this->addChild(_playerNow);
    _gameState = GameState::WAITING;
    
    // place board
    _board = Board::create();
    _board->setPosition(Vec2(winSize.width / 2.0, _board->getContentSize().height / 2.0 + 200));
    this->addChild(_board);
    
    // touch event
    auto listener = EventListenerTouchOneByOne::create();
    // user began touching
    listener->onTouchBegan = [this](Touch* touch, Event* event){
        // call on touch began function
        if(_player != Block::Player::PLAYER1){
            return false;
        }
        onTouchBegan(touch);
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    return true;
}

void SinglePlayerLayer::update(float dt)
{
//    // makes it play against itself
//    if(_updateTimes > 60){
//        if(_gameState == GameState::WAITING)
//        {
//            botMove();
//            _updateTimes = 59;
//        }
//        else if(_gameState == GameState::THINKING )
//        {
//            botMove();
//            _updateTimes = 59;
//        }
//    }
    if(_gameState == GameState::THINKING && 1 < _updateTimes){
        botMove();
        _updateTimes = 0;
    }
    _updateTimes += 1;
}

void SinglePlayerLayer::onTouchBegan(Touch *touch)
{
    Vec2 touchBegan = touch->getLocation();
    // place block
    // if user touches within the board
    if(_board->getBoundingBox().containsPoint(touchBegan)){
        if(_board->makeMoveFromTouch(touch, _player))
        {
            if(_board->checkWin())
            {
                gameDone();
                _gameState = GameState::DONE;
            }
            else if(_board->checkDraw())
            {
                _player = Block::Player::NEITHER;
                gameDone();
                _gameState = GameState::DONE;
            }
            else{
                _player = Block::Player::PLAYER2;
                _playerNow->setTexture("thinking.png");
                _gameState = GameState::THINKING;
                //botMove();
                _updateTimes = 0;
            }
        }
    }
}

void SinglePlayerLayer::botMove()
{
    std::pair<int, int> bestMove;
    bestMove = _bots->monteCarloBot(_board, _player);
    _board->makeMoveFromTile(bestMove, _player);
    if(_board->checkWin())
    {
        _gameState = GameState::DONE;
        gameDone();
        return;
    }
    else if(_board->checkDraw())
    {
        _player = Block::Player::NEITHER;
        _gameState = GameState::DONE;
        gameDone();
        return;
    }
    if(_player == Block::Player::PLAYER1){
        _gameState = GameState::THINKING;
        _player = Block::Player::PLAYER2;
        _playerNow->setTexture("thinking.png");
    }
    else if(_player == Block::Player::PLAYER2){
        _gameState = GameState::WAITING;
        _player = Block::Player::PLAYER1;
        _playerNow->setTexture("yourturn.png");
    }
}

void SinglePlayerLayer::gameDone()
{
    Size winSize = Director::getInstance()->getWinSize();
    GameOverLayer* gameoverlayer = GameOverLayer::create(_player);
    gameoverlayer->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(gameoverlayer);
}