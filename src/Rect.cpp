#include "../include/Rect.h"

Rect::Rect(): x(0.0), y(0.0), w(0.0), h(0.0){
}

Rect::Rect(float x, float y, float w, float h): x(0.0), y(0.0), w(0.0), h(0.0) {
}

bool Rect::Contains(float pointX, float pointY) {
    float y_diff = pointY - y;
    float x_diff = pointX - x;
    return (y_diff < h && y_diff > 0) && (x_diff < w && x_diff > 0);
}

void Rect::SetPosition(float positionX, float positionY) {
    x = positionX;
    y = positionY;
}

void Rect::SumVec2(Vec2 v) {
    x += v.x;
    y += v.y;
}

Vec2 Rect::Center() {
    return Vec2(x + w/2, y + h/2);
}