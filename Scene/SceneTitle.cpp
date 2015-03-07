#include "SceneTitle.h"
#include "../Layer/LayerTitle.h"

USING_NS_CC;

Scene* SceneTitle::create()
{
    //////////////////////////////
    // 1. super init first
    auto scene = Scene::create();
    if ( !scene ){
        return nullptr;
    }
    
    // 'layer' is an autorelease object
    auto layer = LayerTitle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
