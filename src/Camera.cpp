#include "../include/Camera.h"

Vec2 Camera::pos = *(new Vec2());
Vec2 Camera::speed = *(new Vec2());
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus == nullptr) {
        float speedV = 0, speedW = 0;
        if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            speedV = -5;
        }
        else if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            speedV = 5;
        }

        if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            speedW = -5;
        }
        else if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            speedW = 5;
        }

        pos.Sum(Vec2(speedW, speedV));
    }
    else {
        pos.setValues(focus->box.x - (SCREEN_WIDTH/2), focus->box.y - (SCREEN_HEIGHT/2));
    }
}