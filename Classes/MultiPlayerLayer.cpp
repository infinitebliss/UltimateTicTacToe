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

USING_NS_CC;

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
    
    // place board
    _board = Board::create();
    _board->setPosition(Vec2(winSize.width / 2.0, _board->getContentSize().height / 2.0 + 200));
    this->addChild(_board);
    
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
                CCLOG("big tile: %d", bigTileNum);
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
                CCLOG("small tile: %d", smallTileNum);
                break;
            }
        }
        // check if it is already in the map
        std::pair<int, int> tile = std::make_pair(bigTileNum, smallTileNum);
        if(_tileMap.find(tile) != _tileMap.end()){ // already on the map
            return;
        }
        else{ // not on the map yet
            // add block to the board
            // when it is currently player 1's turn
            if(_player == Block::Player::PLAYER1){
                _currentBlock = Block::create(_player);
                _tileMap[tile] = _player;
                _player = Block::Player::PLAYER2;
            }
            // when it is currently player 2's turn
            else if(_player == Block::Player::PLAYER2){
                _currentBlock = Block::create(_player);
                _tileMap[tile] = _player;
                _player = Block::Player::PLAYER1;
            }
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