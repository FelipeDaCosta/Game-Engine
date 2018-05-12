#ifndef SPRITE_H
#define SPRITE_H

#include <cstdlib>
#include <string>
#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Component.h"
#include "Sound.h"
#include "GameObject.h"
#include "Resources.h"
#include "Timer.h"

class Sprite : public Component{
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
        Vec2 scale;
        int frameCount;
        float frameTime;
        int currentFrame;
        float timeElapsed;
        Timer selfDestructCount;
        float secondsToSelfDestruct;
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file, int frameCount = 1, 
               float frameTime = 1, float secondsToSelfDestruct = 0);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        void RenderToPosition(float x, float y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(std::string type);
        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
};

#endif