#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <cmath>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Collider.h"

class Bullet : public Component {
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite);
        ~Bullet();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetDamage();
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};

#endif