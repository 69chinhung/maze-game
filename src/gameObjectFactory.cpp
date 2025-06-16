#include "gameObjectFactory.h"
#include "environment.h"
#include "iconFactory.h"
#include <chrono>
#include <random>
#include <set>
std::random_device rd;
std::mt19937 engine(rd());
std::uniform_int_distribution<int> distX(1, GAME_WINDOW_WIDTH - 2);
std::uniform_int_distribution<int> distY(1, GAME_WINDOW_HEIGHT - 2);

GameObject* SimpleGameObjectFactory::playerGameObject() {
    return new GameObject(IconFactory::NxMColor({1,1}, BLUE), Position{1, 1});
}

GameObject* SimpleGameObjectFactory::wallGameObject(int x, int y) {
    return new GameObject(IconFactory::NxMColor({1,1}, RED), Position{x, y});
}

GameObject* SimpleGameObjectFactory::exitGameObject(int x, int y) {
    return new GameObject(IconFactory::NxMColor({1,1}, GREEN), Position{x, y});
}
