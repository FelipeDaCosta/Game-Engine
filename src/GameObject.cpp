#include "../include/GameObject.h"
#include <iostream>

GameObject::GameObject() {
    isDead = false;
    started = false;
}

void GameObject::Start() {
    for(int i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

GameObject::~GameObject() { 
    for(unsigned int i = 0; i < components.size(); i++) {
        delete components[i];
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for(unsigned int i = 0; i < components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for(unsigned int i = 0; i < components.size(); i++) {
        components[i]->Render();
    }  
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    Sound* finalSound = (Sound*) GetComponent("Sound");
    if(finalSound != nullptr && !finalSound->IsPlaying()) {
        isDead = true; // Play final sound
    }
}

void GameObject::AddComponent(Component * cpt) {
    components.emplace_back(cpt);
    if(started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component * cpt) {
    for(unsigned int i = 0; i < components.size(); i++) {
        if(components[i] == cpt) {
            components.erase(components.begin() + i);
            delete cpt;
        }
    }
}

Component* GameObject::GetComponent(std::string type) {
    Component * cpt = nullptr;
    for(unsigned int i = 0; i < components.size(); i++) {
        if(components[i]->Is(type)) {
            cpt = components[i];
        }
    }
    return cpt;
}