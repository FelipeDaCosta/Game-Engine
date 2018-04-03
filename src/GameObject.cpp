#include "../include/GameObject.h"

GameObject::GameObject() {
    isDead = false;
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
    isDead = true;
}

void GameObject::AddComponent(Component * cpt) {
    components.push_back(cpt);
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