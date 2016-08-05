//
//  TitleScene.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef TitleScene_hpp
#define TitleScene_hpp

#include <stdio.h>

class TitleScene :public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    TitleScene();
    virtual ~TitleScene();
    
public:
    static cocos2d::Scene* createScene();
    bool init() override;
    CREATE_FUNC(TitleScene);
};

#endif /* TitleScene_hpp */
