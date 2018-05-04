#include "../include/Alien.h"

Alien::Alien(GameObject& associated, int mMinions) : Component(associated) {
    associated.AddComponent(new Sprite(associated, "./assets/img/alien.png"));
    hp = 100;
    speed = Vec2(0, 0);
}

void Alien::Start() {

}

Alien::~Alien() {
    for(int i = 0; i < minionArray.size(); i++) {
        minionArray[i].lock()->RequestDelete();
    }
    minionArray.clear();
}

void Alien::Update(float dt) {
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        std::cout << "Click";
        taskQueue.push(* (new Action(Action::SHOOT,
                            InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                            InputManager::GetInstance().GetMouseY() + Camera::pos.y)));
    }
    if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
        std::cout << "Click";
        taskQueue.push(* (new Action(Action::MOVE,
                    InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                    InputManager::GetInstance().GetMouseY() + Camera::pos.y)));
    }

    if(!taskQueue.empty()) {
        Action act = taskQueue.front();
        if(act.type == Action::MOVE) {
            float VELOCITY = 5.0;
            float xDiff = act.pos.x - associated.box.x;
            float yDiff = act.pos.y - associated.box.y;

            float angle = atan2(yDiff, xDiff);

            float xInc = (float)cos(angle)*VELOCITY;
            float yInc = (float)sin(angle)*VELOCITY;
            if(sqrtf(xDiff*xDiff + yDiff*yDiff) < sqrtf(xInc*xInc + yInc*yInc)) {
                xInc = xDiff;
                yInc = yDiff;
                taskQueue.pop();
            }
            associated.box.x += xInc;
            associated.box.y += yInc;
        }
        else {

        }
    }
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return type == "Alien";
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) {
    this->type = type;
    pos = Vec2(x, y);
}