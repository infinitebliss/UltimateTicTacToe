//
//  BigTile.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef BigTile_hpp
#define BigTile_hpp

#include <stdio.h>

#include "SmallTile.hpp"

class BigTile :public cocos2d::Node
{
CC_CONSTRUCTOR_ACCESS:
    BigTile();
    ~BigTile();
    
public:
    bool init(int idx);
    static BigTile* create(int idx);
    
    /* getters & setters start*/
    // tile num
    int getBigTileNum() { return _bigTileNum; }
    
    // yellow bg
    cocos2d::Sprite* getYellowBG() { return _yellowBG; }
    
    // done
    bool getDone() { return _done; }
    void setDone( bool done ) { _done = done; }
    
    // small tile list
    SmallTile** getSmallTileList() { return _smallTileList; }
    /* getters & setters end */
private:
    int _bigTileNum;
    bool _done;
    cocos2d::Sprite* _yellowBG;
    cocos2d::Sprite* _pinkBG;
    cocos2d::Sprite* _blueBG;
    cocos2d::Sprite* _board;
    SmallTile* _smallTileList[9];
};

#endif /* BigTile_hpp */
