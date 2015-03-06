#ifndef __SceneSelect_h__
#define __SceneSelect_h__

#include "cocos2d.h"

class SceneSelect : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* create();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
};

#endif
