#include "../include/Face.h"
#include <iostream> 

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    if(hitpoints > 0) {    
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
}

void Face::Update(float dt) {
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        int mouseX = InputManager::GetInstance().GetMouseX();
        int mouseY = InputManager::GetInstance().GetMouseY();
        if(associated.box.Contains((float) mouseX, (float) mouseY)) {
            this->Damage(std::rand() % 10 + 10);
        }
    }
    if(hitpoints <= 0) {
        associated.RequestDelete(); // Caso toque som de morte tem que deletar aqui
    }
}

void Face::Render() {
}

bool Face::Is(std::string type) {

    return type == "Face";
}