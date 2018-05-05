#include "../include/Alien.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    associated.AddComponent(new Sprite(associated, "./assets/img/alien.png"));
    hp = 100;
    speed = Vec2(0, 0);
    minionArray.resize(nMinions);
}

void Alien::Start() {
    float space = 6.28/minionArray.size();
    for(int i = 0; i < minionArray.size(); i++) {
        GameObject* go = new GameObject();
        std::weak_ptr<GameObject> alienPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);
        Minion* minion = new Minion(*go, alienPtr, i*space);
        go->AddComponent(minion);
        minionArray[i] = Game::GetInstance().GetState().AddObject(go);
    }
}

Alien::~Alien() {
    for(int i = 0; i < minionArray.size(); i++) {
        minionArray[i].lock()->RequestDelete();
    }
    minionArray.clear();
}

void Alien::Update(float dt) {
    associated.angleDeg -= 2;
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(* (new Action(Action::SHOOT,
                            InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                            InputManager::GetInstance().GetMouseY() + Camera::pos.y)));
    }
    if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
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
            std::shared_ptr<GameObject> minionGo = minionArray[rand()%minionArray.size()].lock();
            Minion* minion = (Minion*)minionGo->GetComponent("Minion");
            if(minion == nullptr) {
                std::cout << "Nao foi possivel encontrar um Minion para atirar" << std::endl;
                exit(-1);
            }
            minion->Shoot(act.pos);
            taskQueue.pop();
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