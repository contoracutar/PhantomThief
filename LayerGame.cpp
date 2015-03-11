//
//  LayerGame.cpp
//  PhantomThief
//
//  Created by naohiro nomura on 2015/03/10.
//
//

#include "LayerGame.h"
USING_NS_CC;

LayerGame::LayerGame() : _stage(nullptr){}
LayerGame::~LayerGame(){ CC_SAFE_RELEASE_NULL(_stage); }

bool LayerGame::init(){
    if (!Layer::init()){ return false; }
    auto stage = Stage::create();
    addChild(stage);
    setStage(stage);
    
    scheduleUpdate();
    return true;
}

void LayerGame::update(float delta){
    
}