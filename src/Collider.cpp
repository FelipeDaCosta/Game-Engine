#include "../include/Collider.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset){

}

void Collider::Update(float dt) {
    Rect box = Rect();
    box.w *= scale.x;
    box.h *= scale.y;
    offset.GetRotated(associated.angleDeg);
    box.x = associated.box.Center().x - box.w/2 + offset.x;
    box.y = associated.box.Center().y - box.h/2 + offset.y;
}

void Collider::Render() {

}

bool Collider::Is(std::string type) {
    return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}