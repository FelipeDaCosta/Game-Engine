#include "../include/Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music(std::string file) {
    music = nullptr;
    Open(file);
}

void Music::Play(int times) {
    if(music != nullptr) {
        Mix_PlayMusic(music, times);
    }
    else {
        std::cout << "Tentando tocar musica nullptr" << std::endl;
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);
}