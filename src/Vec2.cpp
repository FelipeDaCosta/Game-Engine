#include "../include/Vec2.h"

Vec2::Vec2() : x(0.0), y(0.0){
}

Vec2::Vec2(float startingX, float startingY) : x(startingX), y(startingY){
}

Vec2 Vec2::GetRotated(float angle) {
    x = x*cos(angle) - y*sin(angle);
    y = y*cos(angle) + x*sin(angle);
    return *this;
}

Vec2 Vec2::Sum(Vec2 vec) {
    x = x + vec.x;
    y = y + vec.y;
    return *this;
}

void Vec2::setValues(float x, float y) {
    this->x = x;
    this->y = x;
}