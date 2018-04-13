#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "../include/Game.h"
#include "../include/Resources.h"


std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    SDL_Texture* returnTexture = nullptr;
    if(imageTable.find(file) == imageTable.end()) { // nao achou
        returnTexture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if(returnTexture == nullptr) {
            std::cout << "Erro no IMG_LoadTexture ao tentar carregar " << file 
                    << ": " << SDL_GetError() << std::endl;
            exit(-1);
        }
        imageTable.insert({file, returnTexture});
        std::cout << "Carregou a textura " << file << std::endl;
    } else {
        returnTexture = (*imageTable.find(file)).second;
    }
    return returnTexture;
}

void Resources::ClearImages() {
    for(auto it = imageTable.begin(); it != imageTable.end(); it++) {
        SDL_DestroyTexture(it->second);
    }
    imageTable.clear();
}


// -------
Mix_Music* Resources::GetMusic(std::string file) {
    Mix_Music* returnMusic = nullptr;
    if(musicTable.find(file) == musicTable.end()) { // nao achou
        returnMusic = Mix_LoadMUS(file.c_str());
        if(returnMusic == nullptr) {
            std::cout << "Erro no MixLoadMUS ao tentar carregar " << file
                    << ": " << SDL_GetError() << std::endl;
            exit(-1);
        }
        musicTable.insert({file, returnMusic});
        std::cout << "Carregou a musica " << file << std::endl;
    } else {
        returnMusic = (*musicTable.find(file)).second;
    }
    return returnMusic;
}

void Resources::ClearMusics() {
    for(auto it = musicTable.begin(); it != musicTable.end(); it++) {
        Mix_FreeMusic(it->second);
    }
    musicTable.clear();
}


// -------
Mix_Chunk* Resources::GetSound(std::string file) {
    Mix_Chunk* returnChunk = nullptr;
    if(soundTable.find(file) == soundTable.end()) { // nao achou
        returnChunk = Mix_LoadWAV(file.c_str());
        if(returnChunk == nullptr) {
        std::cout << "Erro ao abrir arquivo " << file << ": " << SDL_GetError() << std::endl;
        }
        soundTable.insert({file, returnChunk});
        std::cout << "Carregou o chunk " << file << std::endl;
    } else {
        returnChunk = (*soundTable.find(file)).second;
    }
    return returnChunk;
}

void Resources::ClearSounds() {
    for(auto it = soundTable.begin(); it != soundTable.end(); it++) {
        Mix_FreeChunk(it->second);
    }
    soundTable.clear();
}



