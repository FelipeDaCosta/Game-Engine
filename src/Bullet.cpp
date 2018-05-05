#include "../include/Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage,
               float maxDistance, std::string sprite) : Component(associated) {
    this->damage = damage;
    Sprite *bulletSprite = new Sprite(associated, sprite);
    associated.AddComponent(bulletSprite);
    this->speed = Vec2(cos(angle)*speed, sin(angle)*speed);
    distanceLeft = maxDistance - associated.box.Center().Magnitude();
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