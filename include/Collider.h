#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>
#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Rect.h"
#include "Vec2.h"
#include "Game.h"
#include "Camera.h"

class Collider : public Component {
    public:
        Collider(GameObject& associated, Vec2 scale, Vec2 offset);
        Rect box;
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
    private:
        Vec2 scale;
        Vec2 offset;
};

#endif