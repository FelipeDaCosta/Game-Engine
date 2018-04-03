#ifndef STATE_H
#define STATE_H

#include <memory>

#include "Vec2.h"
#include "Sprite.h"
#include "Music.h"
#include "Face.h"

class State {
    private:
        Sprite bg;
        Music music;
        bool quitRequested;
        void Input();
        void AddObject(int mouseX, int mouseY);
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif 