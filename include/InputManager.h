#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <unordered_map>
#define INCLUDE_SDL
#include "SDL_include.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define SPACE_KEY SDLK_SPACE

const int MOUSE_BUTTONS = 6;

class InputManager {
    public:
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);

        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);

        int GetMouseX();
        int GetMouseY();

        bool QuitRequested();

        static InputManager& GetInstance();

    private:
        InputManager();
        ~InputManager();
        bool mouseState[MOUSE_BUTTONS];
        int mouseUpdate[MOUSE_BUTTONS];

        bool quitRequested;
        int updateCounter;

        std::unordered_map<int, bool> keyState;
        std::unordered_map<int, int> keyUpdate;

        int mouseX;
        int mouseY;
};

#endif