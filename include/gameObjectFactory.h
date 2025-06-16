
#ifndef SIMPLE_GAME_OBJECT_FACTORY_H
#define SIMPLE_GAME_OBJECT_FACTORY_H

#include "gameObject.h"

struct SimpleGameObjectFactory {
    static GameObject* playerGameObject();
    static GameObject* wallGameObject(int x, int y);
    static GameObject* exitGameObject(int x, int y);
};

#endif
