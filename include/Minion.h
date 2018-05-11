#ifndef MINION_H
#define MINION_H

#include <string>
#include <cmath>
#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "Collider.h"

class Minion : public Component{
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffSetDeg);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
    private:
        GameObject& alienCenter;
        float arc;
};

#endif