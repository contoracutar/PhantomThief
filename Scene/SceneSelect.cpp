#include "SceneSelect.h"
#include "../Layer/LayerSelect.h"

USING_NS_CC;

Scene* SceneSelect::create()
{
    auto scene = Scene::create();
    if ( !scene ){
        return nullptr;
    }
    
    auto layer = LayerSelect::create();
    
    return scene;
}
