#include "../include/InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager inp;
    return inp;    
}

InputManager::~InputManager() = default;

InputManager::InputManager() {
    quitRequested = false;
    updateCounter = 0;
    mouseX = 0;
    mouseY = 0;
    for(int i = 0; i < MOUSE_BUTTONS; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

void InputManager::Update() {
    SDL_Event event;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            mouseState[event.button.button] = event.type == SDL_MOUSEBUTTONDOWN;
            mouseUpdate[event.button.button] = updateCounter;
		}
		else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            if(event.key.repeat != 1) {
                keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
		}
	}
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}
