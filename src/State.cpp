#include "../include/State.h"

State::State() : bg("./assets/img/ocean.jpg"), music("./assets/audio/stageState.ogg") {
    quitRequested = false;
    music.Play(-1);
}

void State::LoadAssets() {
   
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}

