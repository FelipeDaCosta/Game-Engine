#ifndef RECT_H
#define RECT_H

#include <cmath>
#include <cstdlib>

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
    private:
};

#endif