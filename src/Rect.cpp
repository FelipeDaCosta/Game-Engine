#include "../include/Rect.h"

Rect::Rect(): x(0.0), y(0.0), w(0.0), h(0.0){
}

Rect::Rect(float x, float y, float w, float h): x(0.0), y(0.0), w(0.0), h(0.0) {
}

bool Rect::Contains(float point_x, float point_y) {
    float y_diff = point_y - y;
    float x_diff = point_x - x;
    return (y_diff < h && y_diff > 0) && (x_diff < w && x_diff > 0);
}