#include "../include/Alien.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated) {
    associated.AddComponent(new Sprite(associated, "./assets/img/alien.png"));
    associated.AddComponent(new Collider(associated, Vec2(1, 1), Vec2(0, 0)));
    hp = 100;
    speed = Vec2(0, 0);
    minionArray.resize(nMinions);
    alienCount++;
    state = RESTING;
    restTimer = Timer();
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
    if(hp <= 0) {
        GameObject *goBoom = new GameObject();
        Sprite *boomSprite = new Sprite(*goBoom, "./assets/img/aliendeath.png", 4, 0.2f, 0.8f);
        goBoom->AddComponent(boomSprite);
        goBoom->box.x = associated.box.x;
        goBoom->box.y = associated.box.y;

        Sound *boomSound = new Sound(*goBoom, "./assets/audio/boom.wav");
        goBoom->AddComponent(boomSound);
        boomSound->Play(1);

        Game::GetInstance().GetState().AddObject(goBoom);
        for(int i = 0; i < minionArray.size(); i++) {
            minionArray[i].lock()->RequestDelete();
        }
        minionArray.clear();
        this->associated.RequestDelete();
    }

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

void Alien::NotifyCollision(GameObject& other) {
    Bullet *bul = (Bullet *) other.GetComponent("Bullet");
    if(bul != nullptr && !bul->targetsPlayer) {
        std::cout << "ATACOU ALIEN! ";
        hp -= bul->GetDamage();
        std::cout << "HP: " << hp << std::endl;
    }
}