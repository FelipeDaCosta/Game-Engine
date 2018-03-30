#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string> 
#include <cstdlib>
#include "State.h"
#define INCLUDE_SDL
#include "SDL_include.h"


class Game {
    private:
        Game(std::string title, int width, int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
};

#endif