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
    _board = Sprite::create("board.png");
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