#include "../include/PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(penguinBody) {
    angle = 0;
    Sprite *sprite = new Sprite(associated, "./assets/img/cubngun.png");
    associated.AddComponent(new Collider(associated, Vec2(1, 1), Vec2(0, 0)));
    associated.AddComponent(sprite);
    shootCooldown = Timer();
    shootCooldown.Update(1); // Ja comeca podendo atirar
}

PenguinCannon::~PenguinCannon() {

}

void PenguinCannon::Update(float dt) {
    shootCooldown.Update(dt);
    if(pbody.lock() != nullptr) {
        associated.box.x = pbody.lock()->box.x;
        associated.box.y = pbody.lock()->box.y;

        angle = atan2(InputManager::GetInstance().GetMouseY() + Camera::pos.y - associated.box.y,
                      InputManager::GetInstance().GetMouseX() + Camera::pos.x - associated.box.x);
        associated.angleDeg = angle*180/3.14;
        if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) && shootCooldown.Get() > 0.5) {
            Shoot();
            shootCooldown.Restart();
        }
    }
    else {
        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(std::string type) {
    return type == "PenguinCannon";
}

void PenguinCannon::Shoot() {
    GameObject *bulletGo = new GameObject();
    bulletGo->box.x = associated.box.Center().x;
    bulletGo->box.y = associated.box.Center().y;
    Bullet *bul = new Bullet(*bulletGo, angle, 300, 10, 2000, "./assets/img/minionbullet2.png");
    bulletGo->angleDeg = angle*180/3.14;
    bulletGo->AddComponent(bul);
    Game::GetInstance().GetState().AddObject(bulletGo);
}