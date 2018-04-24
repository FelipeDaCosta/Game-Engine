#define INCLUDE_SDL_IMAGE
#include "../include/Sprite.h"
#include "../include/Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    // Seta width e height
    if(SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        std::cout << "Erro no SDL_QueryTexture: " << SDL_GetError() << std::endl;
    }
    SetClip(0, 0, width, height);
    associated.box.w = width;
    associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::RenderToPosition(float x, float y) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = clipRect.w;
    dstRect.h = clipRect.h;
    if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect) != 0) {
        std::cout << "Erro no SDL_RenderCopy: " << SDL_GetError() << std::endl;
    }
}

void Sprite::Render() {
    RenderToPosition(associated.box.x, associated.box.y);
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::Update(float dt) {
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}