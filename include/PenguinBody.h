#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "InputManager.h"
#include "Collider.h"

class PenguinBody : public Component {
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        Vec2 GetPosition();
        static PenguinBody* player;
        void NotifyCollision(GameObject& other);
        int hp;

    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        float new_angle; // Auxilio para so mudar o angulo quando acelerar
        
};

#endif