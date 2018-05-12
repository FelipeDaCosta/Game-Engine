#include "../include/Minion.h"

Minion::Minion(GameObject& associated, 
               std::weak_ptr<GameObject> alienCenter, float arcOffSetDeg
               ) : Component(associated), alienCenter(*alienCenter.lock()) {
    this->arc = arcOffSetDeg;
    float randScale = ((0.5) * (rand()/(float)RAND_MAX)) + 1.0;
    Sprite *sprite = new Sprite(associated, "./assets/img/minion.png");
    //associated.AddComponent(new Collider(associated, Vec2(1, 1), Vec2(0, 0)));
    sprite->SetScaleX(randScale, randScale);
    associated.AddComponent(sprite);
    associated.angleDeg = arc;
} 

void Minion::Update(float dt) {
    float VELOCITY = 3.14/2;
    arc += VELOCITY*dt;
    Vec2 dOrig = Vec2(200, 0).GetRotated(arc).Sum(alienCenter.box.Center());
    associated.box.SetPosition(dOrig.x - associated.box.w/2, dOrig.y- associated.box.h/2);
    associated.angleDeg += (VELOCITY*dt)*180/3.14;
    if(alienCenter.IsDead()) {
        associated.RequestDelete();
    }
}

void Minion::Render() {

}

bool Minion::Is(std::string type) {
    return type == "Minion";
}

void Minion::Shoot(Vec2 target) {
    GameObject *bulletGo = new GameObject();
    bulletGo->box.x = associated.box.Center().x;
    bulletGo->box.y = associated.box.Center().y;
    float angle = atan2(target.y - bulletGo->box.Center().y, target.x - bulletGo->box.Center().x);
    Bullet *bul = new Bullet(*bulletGo, angle, 300, 10, 200, "./assets/img/minionbullet2.png");
    bulletGo->angleDeg = angle*180/3.14;
    bulletGo->AddComponent(bul);
    Game::GetInstance().GetState().AddObject(bulletGo);
}