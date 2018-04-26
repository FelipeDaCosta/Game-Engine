#ifndef CAMERA_FOLLOWER_H
#define CAMERA_FOLLOWER_H

#include <string.h>
#include "GameObject.h"
#include "Component.h"
#include "Camera.h"

class CameraFollower : public Component {
    public:
        CameraFollower(GameObject& go);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif