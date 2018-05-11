#include "../include/TileSet.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file) : tileSet(associated, file, 1, 1) {
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    if(!tileSet.IsOpen()) {
        std::cout << "Falha ao abrir o tileSet " << file << std::endl;
        exit(1);
    }
    rows = tileSet.GetHeight()/tileHeight;
    columns = tileSet.GetWidth()/tileWidth;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    int row, column;
    if(index < (unsigned)rows*columns) { 
        row = index/columns;
        column = index%columns;
    }
    else {
        std::cout << "Falha ao renderizar tile " << index << std::endl;
        exit(1);
    }
    tileSet.SetClip(column*tileWidth, row*tileHeight, tileWidth, tileHeight);
    tileSet.RenderToPosition(x, y);
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}