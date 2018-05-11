#include "../include/Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite) : Component(associated) {
    this->damage = damage;
    Sprite *bulletSprite = new Sprite(associated, sprite, 3, 1);
    associated.AddComponent(bulletSprite);
    associated.AddComponent(new Collider(associated, Vec2(1, 1), Vec2(0, 0)));
    this->speed = Vec2(cos(angle)*speed, sin(angle)*speed);
    distanceLeft = maxDistance - associated.box.Center().Magnitude();
}

Bullet::~Bullet() {
    std::cout << "Bullet destruida!" << std::endl;
}

void Bullet::Update(float dt) {
    associated.box.SumVec2(speed.Mult(dt));
    distanceLeft -= speed.Mult(dt).Magnitude();
    if(distanceLeft <= 0) associated.RequestDelete();
}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}