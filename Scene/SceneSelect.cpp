#include "SceneSelect.h"
#include "../Layer/LayerSelect.h"

USING_NS_CC;

Scene* SceneSelect::create()
{
    //////////////////////////////
    // 1. super init first
    auto scene = Scene::create();
    if ( !scene ){
        return nullptr;
    }
    
    // 'layer' is an autorelease object
    auto layer = LayerSelect::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
