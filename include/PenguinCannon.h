#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include <string>
#include <cmath>
#include "Component.h"
#include "GameObject.h"
#include "PenguinBody.h"
#include "Collider.h"
#include "Timer.h"

class PenguinCannon : public Component{
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        ~PenguinCannon();
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void Shoot();
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer shootCooldown;
};

#endif