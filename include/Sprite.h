#ifndef SPRITE_H
#define SPRITE_H

#include <cstdlib>
#include <string>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Component.h"
#include "Sound.h"
#include "GameObject.h"
#include "Resources.h"

class Sprite : public Component{
    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;
    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
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
};

#endif