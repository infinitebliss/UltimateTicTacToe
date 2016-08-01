//
//  Block.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "Block.hpp"

USING_NS_CC;

Block::Block()
{
    
}

Block::~Block()
{
    
}

// initialization
bool Block::init(Player player)
{
    if(!Node::init()) return false;
    
    // set image
    if(player == Player::PLAYER1)
    {
        _block = Sprite::create("block_blue.png");
    }
    else if(player == Player::PLAYER2){
        _block = Sprite::create("block_pink.png");
    }
    this->addChild(_block);
    
    // set the size and position
    Size size = Size(70, 70);
    _block->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    this->setContentSize(size);
    this->setAnchorPoint(Vec2(0.5, 0.5));
    return true;
}

// rewrite create function
Block* Block::create(Player player)
{
    Block* block = new Block();
    
    if(block && block->init(player))
    {
        block->autorelease();
        return block;
    }
    
    CC_SAFE_DELETE(block);
    return nullptr;
}