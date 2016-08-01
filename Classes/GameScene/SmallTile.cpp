//
//  SmallTile.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "SmallTile.hpp"

USING_NS_CC;

SmallTile::SmallTile()
{
    
}

SmallTile::~SmallTile()
{
    
}

bool SmallTile::init(int idx)
{
    if(!Node::init()) return false;
    
    _smallTileNum = idx;
    // fixed size
    Size size = Size(75, 75);
    this->setContentSize(size);
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    return true;
}

SmallTile* SmallTile::create(int idx)
{
    SmallTile* smalltile = new SmallTile();
    if(smalltile && smalltile->init(idx))
    {
        smalltile->autorelease();
        return smalltile;
    }
    
    CC_SAFE_DELETE(smalltile);
    return nullptr;
}