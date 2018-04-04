#include "../include/Face.h"
#include <iostream> 

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= 0) {
        Sound *deathSound = (Sound*) associated.GetComponent("Sound");
        if(deathSound != nullptr) {
            deathSound->Play(1);
        }
        associated.RequestDelete(); 
    }
    std::cout << "Tomou dano de " << damage << " vida: " << hitpoints << std::endl;
}

void Face::Update(float dt) {
    if(hitpoints <= 0) {
        associated.RequestDelete(); // Caso toque som de morte tem que deletar aqui
    }
}

void Face::Render() {
}

bool Face::Is(std::string type) {

    return type == "Face";
}