//
//  BigTile.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "BigTile.hpp"

USING_NS_CC;

BigTile::BigTile()
{
    _done = false;
}

BigTile::~BigTile()
{
    
}

bool BigTile::init(int idx)
{
    if(!Node::init()) return false;
    
    // tile number
    _bigTileNum = idx;
    
    // fixed size
    Size size = Size(225, 225);
    
    // place the background and make them not visible for now
    // yellow
    _yellowBG = Sprite::create("tile_background_yellow.png");
    _yellowBG ->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    _yellowBG->setOpacity(80);
    _yellowBG->setVisible(true);
    this->addChild(_yellowBG);
    // blue
    _blueBG = Sprite::create("tile_background_blue.png");
    _blueBG ->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    _blueBG->setOpacity(80);
    _blueBG->setVisible(false);
    this->addChild(_blueBG);
    // yellow
    _pinkBG = Sprite::create("tile_background_pink.png");
    _pinkBG ->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    _pinkBG->setOpacity(80);
    _pinkBG->setVisible(false);
    this->addChild(_pinkBG);
    
    // board image
    _board = Sprite::create("board2.png");
    _board->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    this->addChild(_board);
    
    // fix size
    this->setContentSize(size);
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    // initialize small tiles
    int numOfTiles = 9;
    for(int i = 0; i < numOfTiles; i++){
        SmallTile* tile = SmallTile::create(i);
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
        _smallTileList[i] = tile;
    }
    return true;
}

BigTile* BigTile::create(int idx)
{
    BigTile* bigtile = new BigTile();
    
    if(bigtile && bigtile->init(idx))
    {
        bigtile->autorelease();
        return bigtile;
    }
    
    CC_SAFE_DELETE(bigtile);
    return nullptr;
}