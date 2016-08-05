//
//  LevelScene.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-03.
//
//

#ifndef LevelScene_hpp
#define LevelScene_hpp

#include <stdio.h>

class LevelScene :public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    LevelScene();
    virtual ~LevelScene();
    
public:
    static cocos2d::Scene* createScene();
    bool init() override;
    CREATE_FUNC(LevelScene);
};

#endif /* LevelScene_hpp */
