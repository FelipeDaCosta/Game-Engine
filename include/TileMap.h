#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include "GameObject.h"
#include "TileSet.h"
#include "Component.h"
#include "Camera.h"

class TileMap : public Component{
    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);
        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z);

        void Render();
        void RenderLayer(int layer, int cameraX, int cameraY);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        bool Is(std::string type);
        void Update(float dt);
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};

#endif