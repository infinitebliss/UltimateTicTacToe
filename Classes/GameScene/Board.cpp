//
//  Board.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "Board.hpp"

#include "BigTile.hpp"

USING_NS_CC;

static const int NUM_OF_TILES = 9;

Board::Board()
{
    
}

Board::~Board()
{
    
}

bool Board::init()
{
    if(!Node::init()) return false;
    
    // place board
    _board = Sprite::create("board_big.png");
    Size size = _board->getContentSize();
    _board->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    this->addChild(_board);
    this->setContentSize(size);
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    // initialize big tiles
    int numOfTiles = 9;
    for(int i = 0; i < numOfTiles; i++){
        BigTile* tile = BigTile::create(i);
        Size tileSize = tile->getContentSize();
        this->addChild(tile);
        Vec2 position = Vec2(0, 0);
        if(i == 0){
            position = Vec2(tileSize.width / 2.0, tileSize.height / 2.0 * 5);
        }
        else if(i == 1){
            position = Vec2(tileSize.width / 2.0 * 3, tileSize.height / 2.0 * 5);
        }
        else if(i == 2){
            position = Vec2(tileSize.width / 2.0 * 5, tileSize.height / 2.0 * 5);
        }
        else if(i == 3){
            position = Vec2(tileSize.width / 2.0, tileSize.height / 2.0 * 3);
        }
        else if(i == 4){
            position = Vec2(tileSize.width / 2.0 * 3, tileSize.height / 2.0 * 3);
        }
        else if( i == 5){
            position = Vec2(tileSize.width / 2.0 * 5, tileSize.height / 2.0 * 3);
        }
        else if (i == 6){
            position = Vec2(tileSize.width / 2.0, tileSize.height / 2.0);
        }
        else if ( i == 7){
            position = Vec2(tileSize.width / 2.0 * 3, tileSize.height / 2.0);
        }
        else if ( i == 8){
            position = Vec2(tileSize.width / 2.0 * 5, tileSize.height / 2.0);
        }
        tile->setPosition(position);
        _bigTileList[i] = tile;
    }
    return true;
}

bool Board::checkWin()
{
    // check all 8 cases
    // row 1
    if(_bigTileList[0]->getDone() && _bigTileList[1]->getDone() && _bigTileList[2]->getDone())
    {
        if(_bigTileList[0]->getPlayerWon() == _bigTileList[1]->getPlayerWon()  && _bigTileList[1]->getPlayerWon() == _bigTileList[2]->getPlayerWon()){
            return true;
        }
    }
    // row 2
    if(_bigTileList[3]->getDone() && _bigTileList[4]->getDone() && _bigTileList[5]->getDone())
    {
        if(_bigTileList[3]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[5]->getPlayerWon()){
            return true;
        }
    }
    // row 3
    if(_bigTileList[6]->getDone() && _bigTileList[7]->getDone() && _bigTileList[8]->getDone())
    {
        if(_bigTileList[6]->getPlayerWon() == _bigTileList[7]->getPlayerWon() && _bigTileList[7]->getPlayerWon() == _bigTileList[8]->getPlayerWon()){
            return true;
        }
    }
    // col 1
    if(_bigTileList[0]->getDone() && _bigTileList[3]->getDone() && _bigTileList[6]->getDone())
    {
        if(_bigTileList[0]->getPlayerWon() == _bigTileList[3]->getPlayerWon() && _bigTileList[3]->getPlayerWon() == _bigTileList[6]->getPlayerWon()){
            return true;
        }
    }
    // col 2
    if(_bigTileList[1]->getDone() && _bigTileList[4]->getDone() && _bigTileList[7]->getDone())
    {
        if(_bigTileList[1]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[7]->getPlayerWon()){
            return true;
        }
    }
    // col 3
    if(_bigTileList[2]->getDone() && _bigTileList[5]->getDone() && _bigTileList[8]->getDone())
    {
        if(_bigTileList[2]->getPlayerWon() == _bigTileList[5]->getPlayerWon() && _bigTileList[5]->getPlayerWon() == _bigTileList[8]->getPlayerWon()){
            return true;
        }
    }
    
    // diag 1
    if(_bigTileList[0]->getDone() && _bigTileList[4]->getDone() && _bigTileList[7]->getDone())
    {
        if(_bigTileList[0]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[7]->getPlayerWon()){
            return true;
        }
    }
    
    // diag 2
    if(_bigTileList[2]->getDone() && _bigTileList[4]->getDone() && _bigTileList[6]->getDone())
    {
        if(_bigTileList[2]->getPlayerWon() == _bigTileList[4]->getPlayerWon() && _bigTileList[4]->getPlayerWon() == _bigTileList[6]->getPlayerWon()){
            return true;
        }
    }

    return false;
}

bool Board::checkDraw()
{
    int numOfTilesDone = 0;
    for(int i = 0; i < NUM_OF_TILES; i++)
    {
        BigTile* bigTile = _bigTileList[i];
        if(bigTile->getDone()){
            numOfTilesDone++;
        }
    }
    
    if(numOfTilesDone == NUM_OF_TILES)
    {
        return true;
    }
    return false;
}