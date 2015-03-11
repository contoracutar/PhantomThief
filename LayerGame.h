//
//  LayerGame.h
//  PhantomThief
//
//  Created by naohiro nomura on 2015/03/10.
//
//

#ifndef __PhantomThief__LayerGame__
#define __PhantomThief__LayerGame__

#include "cocos2d.h"
#include "Player.h"
#include "Stage.h"
USING_NS_CC;

class LayerGame : public cocos2d::Layer{
public:
    LayerGame();
    ~LayerGame();
    
    virtual bool init();
    virtual void update (float delta);

    CC_SYNTHESIZE_RETAIN(Stage *, _stage, Stage);
    CREATE_FUNC(LayerGame);
};

#endif /* defined(__PhantomThief__LayerGame__) */
