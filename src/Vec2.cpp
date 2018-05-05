#include "../include/Vec2.h"

Vec2::Vec2() : x(0.0), y(0.0){
}

Vec2::Vec2(float startingX, float startingY) : x(startingX), y(startingY){
}

Vec2 Vec2::GetRotated(float angle) {
    float oldX = x;
    float oldY = y;
    x = oldX*cos(angle) - oldY*sin(angle);
    y = oldY*cos(angle) + oldX*sin(angle);
    return *this;
}

Vec2 Vec2::Sum(Vec2 vec) {
    x = x + vec.x;
    y = y + vec.y;
    return *this;
}

Vec2 Vec2::Mult(float c) {
    return Vec2(x*c, y*c);
}

void Vec2::setValues(float x, float y) {
    this->x = x;
    this->y = x;
}

float Vec2::Magnitude() {
    return sqrtf(x*x + y*y);
}