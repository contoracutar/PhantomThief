//
//  Player.cpp
//  PlayGame
//
//  Created by naohiro nomura on 2015/03/03.
//
//

#include "Player.h"
#define CTS(x) #x

USING_NS_CC;

bool Player::init(){
    initTouch();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    miny = visibleSize.height*0.25f;
    
    const float size = 48;
    
    player = Sprite::create();
    player->setScale(2);
    player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25f));
    this->addChild(player);
    
    Animation *ani[(int)STATE::END];
    for (int i = 0; i < 21; i++) {ani[i] = Animation::create(); }
    Texture2D* texture = TextureCache::sharedTextureCache()->addImage("neko.png");
    int anime[] = { 4, 4, 4, 4, 6, 6, 3, 3, 4, 1, 1 };
    for (int y = 0; y < 21; y++){
        int n = y <= 10 ? y : y - 10;
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
    
    scheduleUpdate();
    return true;
}

void Player::update(float delta){
    int n = (int)dir > 0 ? 0 : 10;
    if (state != oldState || dir != oldDir){
        oldState = state;
        oldDir = dir;
        AnimationRun(strAnimeName[(int)state+n]);
    }
    
    player->setPosition(player->getPosition() + velocity);
    velocity.y-=0.2f;
    player->setPositionY(fmax(miny, player->getPosition().y));

    if (player->getPosition().y > miny){
        state = velocity.y > 0 ? STATE::JUMPUP : STATE::JUMPDOWN;
    }else{
        if (velocity.x != 0){
            state=STATE::RUN;
        }else{
            state=STATE::IDLE;
        }
    }
}

bool Player::onTouchBegan(Touch* touch, Event* event){
    standPos = touch->getLocation();
    return true;
}

void Player::onTouchMoved(Touch* touch, Event* event){
    velocity.x = (touch->getLocation().x - standPos.x) > 0 ? 1 : -1;
    dir = (DIR)velocity.x;
    velocity.x *= 3;
}

void Player::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    velocity.x = 0;
    if (player->getPosition().y == miny) velocity.y = 10;
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

