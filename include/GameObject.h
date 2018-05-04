#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"
#include "Sound.h"

class GameObject {
    public:
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        Rect box;
        void Start();
        bool started;
    private:
        std::vector<Component*> components;
        bool isDead;
};

#endif