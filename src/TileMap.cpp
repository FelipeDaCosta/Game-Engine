#include "../include/TileMap.h"

bool run_once = true;

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated) {
    Load(file);
    this->tileSet = tileSet;
}

void TileMap::Load(std::string file) {
    std::ifstream f;
    f.open(file);
    if(!f.is_open()) {
        std::cout << "Falha ao abrir o arquivo " << file << std::endl;
        exit(1);
    }
    int i = 0;
    char num[10];
    f.getline(num, 10, ',');
    mapWidth = atoi(num);
    f.getline(num, 10, ',');
    mapHeight = atoi(num);
    f.getline(num, 10, ',');
    mapDepth = atoi(num);
    while(f.good()) {
        f.getline(num, 10, ',');
        tileMatrix.push_back(atoi(num) - 1);
        i++;
    }
    f.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
    if(tileSet != nullptr) {
        this->tileSet = tileSet;
    }
    else {
        std::cout << "Tentando colocar tileSet null" << std::endl;
    }
}

int& TileMap::At(int x, int y, int z) {
    return tileMatrix[y*mapWidth + x + mapWidth*mapHeight*z];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    float x, y;
    float parallax = 0.3*layer;
    for(int i = 0; i < GetWidth(); i++) {
        for(int j = 0; j < GetHeight(); j++) {
            x = i*tileSet->GetTileWidth() - cameraX - parallax*Camera::pos.x;
            y = j*tileSet->GetTileHeight() - cameraY - parallax*Camera::pos.y;
            int& index = At(i, j, layer);
            if(!run_once)
                std::cout <<  index << ", ";
            if(index != -1) {
                tileSet->RenderTile(index, x, y);
            }
        }
        if(!run_once)
            std::cout << std::endl;
    }
    run_once = true;
}

void TileMap::Render() {
    for(int i = 0; i < GetDepth(); i++) {
        RenderLayer(i, Camera::pos.x, Camera::pos.y);
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

void TileMap::Update(float dt) {
    
}