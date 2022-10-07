#include "../include/TileSet.h"
#include <stdio.h>
#include <string>

TileSet :: TileSet (int tileWidth, int tileHeight, std :: string file){
	this->tileWidth = (int)tileHeight;
	this->tileHeight = (int)tileWidth;
	
	GameObject *go = new GameObject();
	tileSet = new Sprite(*go, file);
	
	this->rows =  tileSet->GetHeight()/tileHeight;
	this->columns = tileSet->GetWidth()/tileWidth;	
	
}

void TileSet :: RenderTile(int index, float x, float y){
	if(index >= 0 && index < (rows*columns)){
		int clipx = (index%columns) * tileWidth;
		int clipy = (index/columns) * tileHeight;
		tileSet->SetClip(clipx, clipy, tileWidth,tileHeight);
		tileSet->Render(x,y,tileWidth,tileHeight);		
	}
}

int TileSet :: GetTileWidth(){
	return tileWidth;
}

int TileSet :: GetTileHeight(){
	return tileHeight;
}