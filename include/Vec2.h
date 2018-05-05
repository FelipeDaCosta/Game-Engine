#ifndef VEC2_H
#define VEC2_H

#include <cmath>

class Vec2 {
    public:
        Vec2(); // Inicia com x, y = 0
        Vec2(float startingX, float startingY);
        float x;
        float y;
        Vec2 GetRotated(float angle);
        Vec2 Sum(Vec2 vec);
        void setValues(float x, float y);
        float Magnitude();
        Vec2 Mult(float c);
};

#endif