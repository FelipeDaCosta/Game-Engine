#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

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



