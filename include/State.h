#ifndef STATE_H
#define STATE_H

#include <memory>
#include <cstdlib>
#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "Music.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"

class State {
    private:
        Music music;
        bool quitRequested;
        void Input();
       // void AddObject(int mouseX, int mouseY);
        bool started;
        std::vector<std::shared_ptr<GameObject>> objectArray;

    public:
        void Start();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        //std::vector<std::unique_ptr<GameObject>> objectArray;

};

#endif 