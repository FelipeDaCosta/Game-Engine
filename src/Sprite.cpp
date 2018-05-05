#define INCLUDE_SDL_IMAGE
#include "../include/Sprite.h"
#include "../include/Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated), scale(1, 1) {
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated), scale(1, 1) {
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
    dstRect.w = clipRect.w*scale.x;
    dstRect.h = clipRect.h*scale.y;
    if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, 
                        &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0) {
        std::cout << "Erro no SDL_RenderCopyEx: " << SDL_GetError() << std::endl;
    }
}

void Sprite::Render() {
    RenderToPosition(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::Update(float dt) {
}

int Sprite::GetWidth() {
    return width*scale.x;
}

int Sprite::GetHeight() {
    return height*scale.y;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    if(scaleX != 0) {
        scale.x = scaleX;
    }
    if(scaleY != 0) {
        scale.y = scaleY;
    }
}
