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
#include "Box2D/Box2D.h"
#include "GL-ESRender.h"

#define PTM_RATIO 32.0
USING_NS_CC;

class Player : public cocos2d::Layer {
private:
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

    bool wire = false;
    float miny;
    DIR dir, oldDir;
    STATE state, oldState;
    Sprite *player;
    Vec2 velocity = Vec2::ZERO;
    Vec2 standPos = Vec2::ZERO;
    void AnimationRun(std::string name);
    void update(float delta);
    void initTouch();
    void WireAction();
    virtual bool init();
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    float Length(Vec2 v){ return sqrtf(v.x * v.x + v.y * v.y); }
    Vec2 Normalize(Vec2 v){
        float l = Length(v);
        return Vec2(v.x / l, v.y / l);
    }
    float Dot(Vec2 a, Vec2 b){ return a.x * b.x + a.y * b.y; }
    Vec2 Vertical(Vec2 origin, Vec2 v){
        Vec2 unitV = Normalize(v);
        float vLength = Dot(origin, unitV);
        unitV *= vLength;
        return Vec2(origin.x - unitV.x, origin.y - unitV.y);
    }
    bool AABB(Vec2 pos, Vec2 pos2, Vec2 size, Vec2 size2){
        Vec2 p1 = pos + size, p2 = pos2 + size2;
        if (pos.x < p2.x && pos2.x < p1.x && pos.y < p2.y && pos2.y < p1.y){
            return true;
        }
        return false;
    }
    Vec2 posToTileCoordinate(TMXTiledMap *m, Size s, Point point);
    Vec2 tileCoordinateToPos(TMXTiledMap *m, Size s, Point point);
    bool CollisionBox(Sprite *p, TMXTiledMap *m);
    Sprite* addPhysicsBody(cocos2d::TMXLayer *layer, cocos2d::Vec2 &coordinate);
public:
    CREATE_FUNC(Player);
};

#endif /* defined(__PlayGame__Player__) */
