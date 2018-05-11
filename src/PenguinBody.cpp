#include "../include/PenguinBody.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
        speed = Vec2(0, 0);
        linearSpeed = 0;
        angle = 0;
        new_angle = 0;
        hp = 100;
        player = this;
        Sprite *sprite = new Sprite(associated, "./assets/img/penguin.png");
        associated.AddComponent(new Collider(associated, Vec2(1, 1), Vec2(0, 0)));
        associated.AddComponent(sprite);
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    GameObject* cannonGO = new GameObject();
    cannonGO->AddComponent(new PenguinCannon(*cannonGO, Game::GetInstance().GetState().GetObjectPtr(&associated)));
    Game::GetInstance().GetState().AddObject(cannonGO);
    pcannon = Game::GetInstance().GetInstance().GetState().GetObjectPtr(cannonGO);
}

void PenguinBody::Update(float dt) {
    float MAX_SPEED = 10;
    float ACCEL_LINEAR = 2;
    float ACCEL_ANGULAR = 40;
    float STOP_ACCEL = 0.5;

    if(hp <= 0) {
        Camera::Unfollow();
        associated.RequestDelete();
    }

    if(InputManager::GetInstance().IsKeyDown(SDLK_w) && linearSpeed < MAX_SPEED) {
        linearSpeed += ACCEL_LINEAR * dt;
        new_angle = angle;
    }
    else if(InputManager::GetInstance().IsKeyDown(SDLK_s) && linearSpeed > -MAX_SPEED) {
        linearSpeed -= ACCEL_LINEAR * dt;
        new_angle = angle;
    }
    else {
        if(linearSpeed < 0) {
            linearSpeed += STOP_ACCEL*dt;
        }
        else if(linearSpeed > 0) {
            linearSpeed -= STOP_ACCEL*dt;
        }
        if(abs(linearSpeed) < STOP_ACCEL) { linearSpeed = 0;}
    }

    if(InputManager::GetInstance().IsKeyDown(SDLK_a)) {
        angle -= ACCEL_ANGULAR*dt;
    }
    else if(InputManager::GetInstance().IsKeyDown(SDLK_d)) {
        angle += ACCEL_ANGULAR*dt;
    }

    if(InputManager::GetInstance().KeyPress(SDLK_v)) {
        linearSpeed = 0;
    }

    speed.setValues(linearSpeed, 0);
    speed.GetRotated(new_angle*3.14/180);
    associated.box.SumVec2(speed);

    associated.angleDeg = angle;
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(std::string type) {
    return type == "PenguinBody";
}

void PenguinBody::NotifyCollision(GameObject& other) {
    Bullet *bul = (Bullet *) other.GetComponent("Bullet");
    if(bul != nullptr && bul->targetsPlayer)
        std::cout << "Colidiu!" << std::endl;
}