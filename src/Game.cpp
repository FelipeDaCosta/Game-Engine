#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/Game.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
    if(instance == nullptr) {
        instance = new Game("Felipe da Costa Malaquias 13/0044440", 1024, 600);
    }
    return *instance;
}

Game::Game(std::string title, int width, int height) {
    srand(time(NULL));
    if(instance != nullptr) {
        std::cout << "Tentativa de criar segunda classe Game" << std::endl;
        exit(-1);
    }
    // Inicializar SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << "Falha no SDL_Init: " << SDL_GetError() << std::endl;
        exit(-1);
    }

    // Inicializar IMG
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    if(IMG_Init(imgFlags) != imgFlags) {
        std::cout << "Falha no IMG_Init: " << SDL_GetError() << std::endl;
    }

    // Inicializar mixer
    int mixerFlags = MIX_INIT_OGG;
    if(Mix_Init(mixerFlags) != mixerFlags) {
        std::cout << "Falha no Mix_Init: " << SDL_GetError() << std::endl;
    }
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, 
        MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
            std::cout << "Falha no MixOpenAudio: " << std::endl;
    }
    Mix_AllocateChannels(32);

    // Janela
    window = SDL_CreateWindow(title.c_str(), 
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == nullptr) {
        std::cout << "Falha no SDL_Createwindow: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    // Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        std::cout << "Falha no SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        exit(-1);
    }
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

State& Game::GetState() {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    state = new State();
    while(state->QuitRequested() == false) {
        InputManager::GetInstance().Update();
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}