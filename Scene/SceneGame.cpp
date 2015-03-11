//
//  SceneGame.cpp
//  PhantomThief
//
//  Created by naohiro nomura on 2015/03/10.
//
//

#include "SceneGame.h"
#include "LayerGame.h"

USING_NS_CC;

Scene* SceneGame::create()
{
    auto scene = Scene::createWithPhysics();
    if ( !scene ){
        return nullptr;
    }
    
//    auto world = scene->getPhysicsWorld();
//    world->setGravity(Vec2(0, -500));
    //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [](PhysicsContact &contact){
        return true;
    };
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto layer = LayerGame::create();
    scene->addChild(layer);

    return scene;
}
