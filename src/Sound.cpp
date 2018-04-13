#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "../include/Sound.h"

Sound::Sound(GameObject& associated) : Component(associated) {
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated) {
    Open(file);
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop() {
    if(chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
}

bool Sound::IsPlaying() {
    return Mix_Playing(channel);
}

void Sound::Update(float dt) {
}

void Sound::Render() {
}

bool Sound::Is(std::string type) {
    return type == "Sound";
}

Sound::~Sound() {
    if(chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}

