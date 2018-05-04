#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Camera.h"

class Alien : public Component {
    public:
        Alien(GameObject& associated, int mMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
    private:
        class Action {
            public:
                enum ActionType {MOVE, SHOOT};
                Action(ActionType type, float x, float y);
                ActionType type;
                Vec2 pos;
        };
        Vec2 speed;
        int hp;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif