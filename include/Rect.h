#ifndef RECT_H
#define RECT_H

#include <cmath>
#include <cstdlib>
#include "Vec2.h"

class Rect {
    public:
        float x;
        float y;
        float w;
        float h;
        Rect(); // Inicializa tudo 0
        Rect(float x, float y, float w, float h);
        void SetPosition(float x, float y);
        bool Contains(float x, float y);
        void SumVec2(Vec2 v);
        Vec2 Center();
    private:
};

#endif