#include "../include/TileMap.h"

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
    for(int i = 0; i < GetWidth(); i++) {
        for(int j = 0; j < GetHeight(); j++) {
            float x, y;
            x = i*tileSet->GetTileWidth() - cameraX;
            y = j*tileSet->GetTileHeight() - cameraY;
            int& index = At(i, j, layer);
            if(index != -1) {
                tileSet->RenderTile(At(i, j, layer), x, y);
            }
        }
    }
}

void TileMap::Render() {
    for(int i = 0; i < GetDepth(); i++) {
        RenderLayer(i, 0, 0);
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