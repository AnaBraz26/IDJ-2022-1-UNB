#include "../include/SDL_include.h"
#include "../include/Sprite.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

TileMap :: TileMap(GameObject& associated, std::string file, TileSet* tileSet): Component(associated){
	 Load(file);
	 this->tileSet = tileSet;
}

void TileMap :: Load(std::string file){	
	ifstream fin;
    int tmp;
    char discard;
    fin.open(file);
    fin >> mapWidth >> discard >> mapHeight >> discard >> mapDepth;
    for (int i = 0; i < mapDepth; i++) {
        fin >> discard;
        for (int j = 0; j < mapHeight; j++) {
            for (int k = 0; k < mapWidth; k++) {
                fin >> tmp >> discard;
                tmp--;
                tileMatrix.push_back(tmp);
            }
        }
    }
}

//Troca o tileSet em uso
void TileMap :: SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}

// retorna uma referência ao elemento [x][y][z] de tileMatrix.
int& TileMap :: At(int x, int y, int z){
	return tileMatrix.at(x + (y * mapWidth) + (z * mapHeight * mapWidth));
}

//Renderiza as camadas do mapa.
void TileMap :: Render(){
	for(int i = 0; i < mapDepth; i++){
		RenderLayer(i);
	}
}

// Renderiza uma camada do mapa, tile a tile.
void TileMap :: RenderLayer(int layer, int cameraX, int cameraY){
	for(int i = 0; i < mapHeight; i++){
		for(int j = 0; j < mapWidth; j++){
			int x = j * tileSet->GetTileWidth();
			int y = i * tileSet->GetTileHeight();
			tileSet->RenderTile(At(j,i,layer), x - Camera :: pos.x, y - Camera::pos.y);
		}
	}
}

int TileMap :: GetWidth(){
	return mapWidth;
}

int TileMap :: GetHeight(){
	return mapHeight;
}

int TileMap :: GetDepth(){
	return mapDepth;
}

bool TileMap :: Is(std :: string type){
	if(type == "TileMap"){
		return true;
	}
	return false;
}

void TileMap :: Update(float dt){

}