//
//  Player.cpp
//  PlayGame
//
//  Created by naohiro nomura on 2015/03/03.
//
//

#include "Player.h"
#include "LayerTitle.h"
#include "Stage.h"

USING_NS_CC;

bool Player::init(){
    initTouch();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    miny = visibleSize.height*0.25f;
    
    const float size = 48;
    
    player = Sprite::create();
    player->setScale(2);
    player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3f));
    
    Animation *ani[(int)STATE::END];
    for (int i = 0; i < 21; i++) {ani[i] = Animation::create(); }
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage("neko.png");
    int anime[] = { 4, 4, 4, 4, 6, 6, 3, 3, 4, 1, 1 };
    for (int y = 0; y < (int)STATE::END; y++){
        int n = y < 10 ? y : y - 10;
        for (int x = 0; x < anime[n]; x++){
            Rect rect = Rect(x * size, y * size, size, size);
            ani[y]->addSpriteFrameWithTexture(texture, rect);
        }
        ani[y]->setDelayPerUnit(0.125f);
        ani[y]->setRestoreOriginalFrame(true);
        ani[y]->setLoops(-1);
    }
    AnimationCache *aniCache = AnimationCache::sharedAnimationCache();
    for (int i = 0; i < (int)STATE::END; i++){
        aniCache->addAnimation(ani[i], strAnimeName[i]);
    }
    
    AnimationRun(strAnimeName[(int)STATE::IDLE]);
    
    auto mat = PhysicsMaterial();
    mat.friction = 0;
    auto body = PhysicsBody::createBox(Size(size, size * 1.75f), mat);
    body->setRotationEnable(false);
    body->setCategoryBitmask(static_cast<int>(Stage::TILETYPE::PLAYER));
    body->setCollisionBitmask(static_cast<int>(Stage::TILETYPE::PLAYER));
    body->setContactTestBitmask(INT_MAX);
    //body->setGravityEnable(false);
    //body->setDynamic(false);
    player->setPhysicsBody(body);
    
    this->addChild(player);
    
    scheduleUpdate();
    return true;
}

void Player::update(float delta){
    int n = (int)dir > 0 ? 0 : 10;
    if (state != oldState || dir != oldDir){
        if (state != STATE::JUMPUP && oldState == STATE::JUMPDOWN){
            velocity = Vec2::ZERO;
        }
        AnimationRun(strAnimeName[(int)state+n]);
        oldState = state;
        oldDir = dir;
    }
    
    //player->setPosition(player->getPosition() + velocity);
    Vec2 gravity = Vec2(0, -0.2f);
    player->getPhysicsBody()->applyImpulse(velocity);
    //velocity += gravity;
    //player->setPositionY(fmax(miny, player->getPosition().y));

    Vec2 pos = player->getPosition();
    
    removeChildByTag(99);
    if (pos.y > miny){
        state = velocity.y > 0 ? STATE::JUMPUP : STATE::JUMPDOWN;
        if (wire){
            auto w = DrawNode::create();
            w->drawSegment(pos, standPos, 1, Color4F::WHITE);
            addChild(w, 0, 99);
            float leng = Length(standPos - pos);
            Vec2 vector = Vec2(pos.x - standPos.x, pos.y - standPos.y);
            Vec2 unit = Normalize(vector);
            velocity = Vertical(velocity + Vertical(gravity, vector), vector);
            pos = standPos + unit * leng;
        }
    }else{
        wire = false;
        if (velocity.x != 0){
            state=STATE::RUN;
        }else{
            state=STATE::IDLE;
        }
    }
}

bool Player::onTouchBegan(Touch* touch, Event* event){
    standPos = touch->getLocation();
    
    Vec2 screen = Director::getInstance()->getVisibleSize();
    if (standPos.y > screen.y / 2){
        wire = true;
    }
    return true;
}

void Player::onTouchMoved(Touch* touch, Event* event){
    if (!wire){
        velocity.x = (touch->getLocation().x - standPos.x) > 0 ? 1 : -1;
        dir = (DIR)velocity.x;
        velocity.x *= 3;
    }
}

void Player::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    if (!wire){
        velocity.x = 0;
        //if (player->getPosition().y < miny) velocity.y = 10;
        //player->getPhysicsBody()->setVelocity(Vec2(0));
        player->getPhysicsBody()->applyImpulse(Vec2(0, 400));
    }
    wire = false;
}

Vec2 Player::tileCoordinateToPos(TMXTiledMap *m, Size s, Vec2 p){
    float size = 2;
    float x = floor(s.width/2 * size + p.x * m->getTileSize().width * size);
    float y = floor(s.height/2 * size + p.y * m->getTileSize().height * size);
    return Vec2(x, y);
}

Vec2 Player::posToTileCoordinate(TMXTiledMap *m, Size s, Vec2 p){
    float size = 2;
    float x = floor((p.x - s.width/2 * size) / (m->getTileSize().width * size));
    float y = floor((p.y - s.height/2 * size) / (m->getTileSize().height * size));
    return Vec2(x, y);
}

void Player::WireAction(){
}

void Player::initTouch(){
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Player::AnimationRun(std::string name){
    player->stopAllActions();
    AnimationCache *animationCache = AnimationCache::sharedAnimationCache();
    Animation *animation = animationCache->animationByName(name);
    RepeatForever *action = RepeatForever::create( Animate::create(animation) );
    player->runAction(action);
}
