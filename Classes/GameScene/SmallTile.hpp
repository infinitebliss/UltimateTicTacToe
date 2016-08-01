//
//  SmallTile.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef SmallTile_hpp
#define SmallTile_hpp

#include <stdio.h>

class SmallTile :public cocos2d::Node
{
CC_CONSTRUCTOR_ACCESS:
    SmallTile();
    virtual ~SmallTile();
    
public:
    bool init(int idx);
    static SmallTile* create(int idx);
    
    /* getters & setters start*/
    // small tile num
    int getSmallTileNum() { return _smallTileNum; }
    /* getters & setters end */

    
private:
    int _smallTileNum;
};

#endif /* SmallTile_hpp */
