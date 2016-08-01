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

const int NUM_OF_TILES = 9;

MultiPlayerLayer::MultiPlayerLayer()
{
    _player = Block::Player::PLAYER1;
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
    
    // place board
    _board = Board::create();
    _board->setPosition(Vec2(winSize.width / 2.0, _board->getContentSize().height / 2.0 + 200));
    this->addChild(_board);
    
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
                // remove the block placed
                _currentBlock->removeFromParent();
                // remove from tile map
                std::map<std::pair<int, int>, Block::Player>::iterator it;
                it = _tileMap.find(_tile);
                _tileMap.erase(it);
                // make button diabled
                _undo->setBright(false);
                // reset current tile
                checkBigTileForWin(_tile.first);
                // reset available big tiles
                if(_tileMap.empty()){ // undo first move
                    // put all big tiles in available big tile vector initially
                    int numOfTiles = 9;
                    for( int i = 0; i < numOfTiles; i++)
                    {
                        _availableBigTiles.push_back(i);
                    }
                    BigTile** bigTileList = _board->getBigTileList();
                    // then set the ones that are in the available big tile vector as visible
                    for(auto it = _availableBigTiles.begin(); it != _availableBigTiles.end(); it++)
                    {
                        BigTile* bigTile = bigTileList[(*it)];
                        Sprite* yellowbg = bigTile->getYellowBG();
                        yellowbg->setVisible(true);
                    }
                }
                else{
                   resetAvailableBigTiles(_tile.first);
                }
                
                break;
            }
            default:
                break;
        }
    });
    this->addChild(_undo);
    _undo->setBright(false);

    
    // put all big tiles in available big tile vector initially
    int numOfTiles = 9;
    for( int i = 0; i < numOfTiles; i++)
    {
        _availableBigTiles.push_back(i);
    }
    
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
        BigTile** bigTileList = _board->getBigTileList();
        Vec2 touchBoardBegan = _board->convertTouchToNodeSpace(touch);
        int numOfTiles = 9;
        // find which big tile user is touching
        int bigTileNum = -1;
        BigTile* bigTile = NULL;
        for(auto it = _availableBigTiles.begin(); it != _availableBigTiles.end(); it++){
            bigTile = bigTileList[(*it)];
            if(bigTile->getBoundingBox().containsPoint(touchBoardBegan)){
                bigTileNum =  bigTile->getBigTileNum();
                break;
            }
        }
        // if its not in the available tile list
        if(bigTileNum == -1){
            return;
        }
        // find which small tile user is touching
        SmallTile** smallTileList = bigTile->getSmallTileList();
        Vec2 touchBigTileBegan = bigTile->convertTouchToNodeSpace(touch);
        int smallTileNum = 0;
        SmallTile* smallTile;
        for(int i = 0; i < numOfTiles; i++){
            smallTile = smallTileList[i];
            if(smallTile->getBoundingBox().containsPoint(touchBigTileBegan)){
                smallTileNum = smallTile->getSmallTileNum();
                break;
            }
        }
        // check if it is already in the map
        _tile = std::make_pair(bigTileNum, smallTileNum);
        if(_tileMap.find(_tile) != _tileMap.end()){ // already on the map
            return;
        }
        else{ // not on the map yet
            // add block to the board
            // when it is currently player 1's turn
            if(_player == Block::Player::PLAYER1){
                _currentBlock = Block::create(_player);
                _tileMap[_tile] = _player;
                checkBigTileForWin(bigTileNum);
                checkBigTileFull(bigTileNum);
                checkBoardForWin();
                checkBoardFull();
                // set next player
                _player = Block::Player::PLAYER2;
                _playerNow->setTexture("player2.png");
            }
            // when it is currently player 2's turn
            else if(_player == Block::Player::PLAYER2){
                _currentBlock = Block::create(_player);
                _tileMap[_tile] = _player;
                checkBigTileForWin(bigTileNum);
                checkBigTileFull(bigTileNum);
                checkBoardForWin();
                checkBoardFull();
                // set next player
                _player = Block::Player::PLAYER1;
                _playerNow->setTexture("player1.png");
            }
            _undo->setBright(true);
            _currentBlock->setPosition(Vec2(smallTile->getContentSize().width / 2.0, smallTile->getContentSize().height / 2.0));
            smallTile->addChild(_currentBlock);
        }
        
        // reset available big tiles
        resetAvailableBigTiles(smallTileNum);
    }
}
void MultiPlayerLayer::resetAvailableBigTiles(int nextSmallTileNum)
{
    // clear current available big tile list
    _availableBigTiles.clear();
    
    BigTile** bigTileList = _board->getBigTileList();
    BigTile* bigTile = bigTileList[nextSmallTileNum];
    
    // check if next small tile num is done
    if(!bigTile->getDone())
    {
        _availableBigTiles.push_back(nextSmallTileNum);
    }
    else
    {
        int numOfTiles = 9;
        for(int i = 0; i < numOfTiles; i++)
        {
            bigTile = bigTileList[i];
            if(!bigTile->getDone())
            {
                _availableBigTiles.push_back(i);
            }
        }
    }
    
    // reset the yellowbg of the big tiles
    // set all of the yellowbg visiblity to false first
    int numOfTiles = 9;
    for(int i = 0; i < numOfTiles; i++)
    {
        bigTile = bigTileList[i];
        Sprite* yellowbg = bigTile->getYellowBG();
        yellowbg->setVisible(false);
    }
    // then set the ones that are in the available big tile vector as visible
    for(auto it = _availableBigTiles.begin(); it != _availableBigTiles.end(); it++)
    {
        bigTile = bigTileList[(*it)];
        Sprite* yellowbg = bigTile->getYellowBG();
        yellowbg->setVisible(true);
    }
}

void MultiPlayerLayer::checkBigTileFull(int bigTileNum)
{
    std::pair<int, int> tile0 = std::make_pair(bigTileNum, 0);
    std::pair<int, int> tile1 = std::make_pair(bigTileNum, 1);
    std::pair<int, int> tile2 = std::make_pair(bigTileNum, 2);
    std::pair<int, int> tile3 = std::make_pair(bigTileNum, 3);
    std::pair<int, int> tile4 = std::make_pair(bigTileNum, 4);
    std::pair<int, int> tile5 = std::make_pair(bigTileNum, 5);
    std::pair<int, int> tile6 = std::make_pair(bigTileNum, 6);
    std::pair<int, int> tile7 = std::make_pair(bigTileNum, 7);
    std::pair<int, int> tile8 = std::make_pair(bigTileNum, 8);
    BigTile** bigTileList = _board->getBigTileList();
    BigTile* bigTile = bigTileList[bigTileNum];
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile1) != _tileMap.end()) && (_tileMap.find(tile2) != _tileMap.end()) && (_tileMap.find(tile3) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile5) != _tileMap.end()) && (_tileMap.find(tile6) != _tileMap.end()) && (_tileMap.find(tile7) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        bigTile->setDone(true);
        bigTile->setPlayerWon(Block::Player::NEITHER);
    }

}


void MultiPlayerLayer::checkBigTileForWin(int bigTileNum)
{
    // checks all 8 cases
    std::pair<int, int> tile0 = std::make_pair(bigTileNum, 0);
    std::pair<int, int> tile1 = std::make_pair(bigTileNum, 1);
    std::pair<int, int> tile2 = std::make_pair(bigTileNum, 2);
    std::pair<int, int> tile3 = std::make_pair(bigTileNum, 3);
    std::pair<int, int> tile4 = std::make_pair(bigTileNum, 4);
    std::pair<int, int> tile5 = std::make_pair(bigTileNum, 5);
    std::pair<int, int> tile6 = std::make_pair(bigTileNum, 6);
    std::pair<int, int> tile7 = std::make_pair(bigTileNum, 7);
    std::pair<int, int> tile8 = std::make_pair(bigTileNum, 8);
    BigTile** bigTileList = _board->getBigTileList();
    BigTile* bigTile = bigTileList[bigTileNum];
    bigTile->setDone(false);
    bigTile->getBlueBG()->setVisible(false);
    bigTile->getPinkBG()->setVisible(false);
    // row 1
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile1) != _tileMap.end()) && (_tileMap.find(tile2) != _tileMap.end()))
    {
        if(_tileMap[tile0] == _player && _tileMap[tile1] == _player && _tileMap[tile2] == _player) {
            bigTile->setDone(true);
        }
    }
    // row 2
    if((_tileMap.find(tile3) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile5) != _tileMap.end()))
    {
        if(_tileMap[tile3] == _player && _tileMap[tile4] == _player && _tileMap[tile5] == _player) {
            bigTile->setDone(true);
        }
    }
    // row 3
    if((_tileMap.find(tile6) != _tileMap.end()) && (_tileMap.find(tile7) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        if(_tileMap[tile6] == _player && _tileMap[tile7] == _player && _tileMap[tile8] == _player) {
            bigTile->setDone(true);
        }
    }
    // col 1
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile3) != _tileMap.end()) && (_tileMap.find(tile6) != _tileMap.end()))
    {
        if(_tileMap[tile0] == _player && _tileMap[tile3] == _player && _tileMap[tile6] == _player) {
            bigTile->setDone(true);
        }
    }
    // col 2
    if((_tileMap.find(tile1) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile7) != _tileMap.end()))
    {
        if(_tileMap[tile1] == _player && _tileMap[tile4] == _player && _tileMap[tile7] == _player) {
            bigTile->setDone(true);
        }
    }
    // col 3
    if((_tileMap.find(tile2) != _tileMap.end()) && (_tileMap.find(tile5) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        if(_tileMap[tile2] == _player && _tileMap[tile5] == _player && _tileMap[tile8] == _player) {
            bigTile->setDone(true);
        }
    }
    
    // diag 1
    if((_tileMap.find(tile0) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile8) != _tileMap.end()))
    {
        if(_tileMap[tile0] == _player && _tileMap[tile4] == _player && _tileMap[tile8] == _player) {
            bigTile->setDone(true);
        }
    }
    
    // diag 2
    if((_tileMap.find(tile2) != _tileMap.end()) && (_tileMap.find(tile4) != _tileMap.end()) && (_tileMap.find(tile6) != _tileMap.end()))
    {
        if(_tileMap[tile2] == _player && _tileMap[tile4] == _player && _tileMap[tile6] == _player) {
            bigTile->setDone(true);
        }
    }
    
    // change bg
    if(bigTile->getDone()){
        if(_player == Block::Player::PLAYER1) {
            bigTile->getBlueBG()->setVisible(true);
        }
        else{
            bigTile->getPinkBG()->setVisible(true);
        }
        bigTile->setPlayerWon(_player);
    }
}

void MultiPlayerLayer::checkBoardForWin()
{
    // check all 8 cases
    BigTile** bigTileList = _board->getBigTileList();
    
    // row 1
    if(bigTileList[0]->getDone() && bigTileList[1]->getDone() && bigTileList[2]->getDone())
    {
        if(bigTileList[0]->getPlayerWon() == _player && bigTileList[1]->getPlayerWon() == _player && bigTileList[2]->getPlayerWon() == _player){
            gameDone();
        }
    }
    // row 2
    if(bigTileList[3]->getDone() && bigTileList[4]->getDone() && bigTileList[5]->getDone())
    {
        if(bigTileList[3]->getPlayerWon() == _player && bigTileList[4]->getPlayerWon() == _player && bigTileList[5]->getPlayerWon() == _player){
            gameDone();
        }
    }
    // row 3
    if(bigTileList[6]->getDone() && bigTileList[7]->getDone() && bigTileList[8]->getDone())
    {
        if(bigTileList[6]->getPlayerWon() == _player && bigTileList[7]->getPlayerWon() == _player && bigTileList[8]->getPlayerWon() == _player){
            gameDone();
        }
    }
    // col 1
    if(bigTileList[0]->getDone() && bigTileList[3]->getDone() && bigTileList[6]->getDone())
    {
        if(bigTileList[0]->getPlayerWon() == _player && bigTileList[3]->getPlayerWon() == _player && bigTileList[6]->getPlayerWon() == _player){
            gameDone();
        }
    }
    // col 2
    if(bigTileList[1]->getDone() && bigTileList[4]->getDone() && bigTileList[7]->getDone())
    {
        if(bigTileList[1]->getPlayerWon() == _player && bigTileList[4]->getPlayerWon() == _player && bigTileList[7]->getPlayerWon() == _player){
            gameDone();
        }
    }
    // col 3
    if(bigTileList[2]->getDone() && bigTileList[5]->getDone() && bigTileList[8]->getDone())
    {
        if(bigTileList[2]->getPlayerWon() == _player && bigTileList[5]->getPlayerWon() == _player && bigTileList[8]->getPlayerWon() == _player){
            gameDone();
        }
    }
    
    // diag 1
    if(bigTileList[0]->getDone() && bigTileList[4]->getDone() && bigTileList[7]->getDone())
    {
        if(bigTileList[0]->getPlayerWon() == _player && bigTileList[4]->getPlayerWon() == _player && bigTileList[7]->getPlayerWon() == _player){
            gameDone();
        }
    }
    
    // diag 2
    if(bigTileList[2]->getDone() && bigTileList[4]->getDone() && bigTileList[6]->getDone())
    {
        if(bigTileList[2]->getPlayerWon() == _player && bigTileList[4]->getPlayerWon() == _player && bigTileList[6]->getPlayerWon() == _player){
            gameDone();
        }
    }
}

void MultiPlayerLayer::checkBoardFull()
{
    int numOfTilesDone = 0;
    BigTile** bigTileList = _board->getBigTileList();
    for(int i = 0; i < NUM_OF_TILES; i++)
    {
        BigTile* bigTile = bigTileList[i];
        if(bigTile->getDone()){
            numOfTilesDone++;
        }
    }
    
    if(numOfTilesDone == NUM_OF_TILES)
    {
        _player = Block::Player::NEITHER;
        gameDone();
    }
}

void MultiPlayerLayer::gameDone()
{
    Size winSize = Director::getInstance()->getWinSize();
    GameOverLayer* gameoverlayer = GameOverLayer::create(_player);
    gameoverlayer->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(gameoverlayer);
}