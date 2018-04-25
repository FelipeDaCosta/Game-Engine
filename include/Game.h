#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string> 
#include <cstdlib>
#define INCLUDE_SDL
#include "SDL_include.h"
#include <ctime>
#include "State.h"
#include "InputManager.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 600;

class State;

class Game {
    private:
        Game(std::string title, int width, int height);
        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;
        int frameStart;
        float dt;
        void CalculateDeltaTime();
    public:
        ~Game();
        void Run();
        SDL_Renderer* GetRenderer();
        State& GetState();
        static Game& GetInstance();
        float GetDeltaTime();
};

#endif