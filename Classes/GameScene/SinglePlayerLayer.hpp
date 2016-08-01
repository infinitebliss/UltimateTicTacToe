//
//  SinglePlayerLayer.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-07-29.
//
//

#ifndef SinglePlayerLayer_hpp
#define SinglePlayerLayer_hpp

#include <stdio.h>

class SinglePlayerLayer : public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    SinglePlayerLayer();
    virtual ~SinglePlayerLayer();
    
public:
    CREATE_FUNC(SinglePlayerLayer);
    
    bool init()override;
};

#endif /* SinglePlayerLayer_hpp */
