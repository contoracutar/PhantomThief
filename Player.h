//
//  Player.h
//  PlayGame
//
//  Created by naohiro nomura on 2015/03/03.
//
//

#ifndef __PlayGame__Player__
#define __PlayGame__Player__

#include <stdio.h>
USING_NS_CC;

class Player : public cocos2d::Layer {
public:
//    enum STATE{
//        R_IDLE, R_IDLE2, R_ATTACK, R_HOLD, R_RUN,
//        R_HOLDRUN, R_JUMPUP, R_JUMPDOWN, R_CLIMB, R_DAMAGE,
//        L_IDLE, L_IDLE2, L_ATTACK, L_HOLD, L_RUN,
//        L_HOLDRUN, L_JUMPUP, L_JUMPDOWN, L_CLIMB, L_DAMAGE, DIE, END
//    };
    enum class DIR{
        LEFT = -1, RIGHT = 1
    };
    enum class STATE{
        IDLE, IDLE2, ATTACK, HOLD, RUN, HOLDRUN, JUMPUP, JUMPDOWN, CLIMB, DAMAGE,
        DIE = 20, END
    };
    std::string strAnimeName[(int)STATE::END] = {
        "R_Idle", "R_Idle2", "R_Attack", "R_Hold", "R_Run",
        "R_HoldRun", "R_JumpUp", "R_JumpDown", "R_Climb", "R_Damage",
        "L_Idle", "L_Idle2", "L_Attack", "L_Hold", "L_Run",
        "L_HoldRun", "L_JumpUp", "L_JumpDown", "L_Climb", "L_Damage", "Die"
    };

    float miny;
    DIR dir, oldDir;
    STATE state, oldState;
    Sprite *player;
    Vec2 velocity = Vec2::ZERO;
    Vec2 standPos = Vec2::ZERO;
    void AnimationRun(std::string name);
    void update(float delta);
    void initTouch();
    virtual bool init();
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    CREATE_FUNC(Player);
};

#endif /* defined(__PlayGame__Player__) */
