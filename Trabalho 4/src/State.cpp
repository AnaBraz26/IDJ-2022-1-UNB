#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/State.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"

State :: State(){
	GameObject *go = new GameObject();
	GameObject *oceano = new GameObject();

	Sprite *bg = new Sprite(*oceano,"img/ocean.jpg");
	oceano->AddComponent(bg);

	CameraFollower *camfow = new CameraFollower(*oceano);
	oceano->AddComponent(camfow);

	oceano->box.x = Camera::pos.x;
	oceano->box.y = Camera::pos.y;
	//oceano->box.w = bg->GetWidth();
	//oceano->box.h = bg->GetHeight();
	objectArray.emplace_back(oceano);

	TileSet *tileset = new TileSet(64,64,"img/tileset.png");

	TileMap *tilemap = new TileMap(*go,"map/tileMap.txt", tileset);
	go->AddComponent(tilemap);
	go->box.x = 0;
	go->box.y = 0;
	objectArray.emplace_back(go);

	music = new Music("audio/stageState.ogg");
	music->Play();

	quitRequested = false;
}

State :: ~State(){
	objectArray.clear();
}

void State :: LoadAssets(){

}

void State :: Update(float dt){
	InputManager instance = InputManager::GetInstance();
	if(instance.KeyPress(ESCAPE_KEY) || instance.Quitresquested()){
		quitRequested = true;
	}
	if(instance.KeyPress(SPACEBAR)){
		Vec2 objPos = Vec2( 200, 0 ).rotate( -50 + 50*(rand() % 1001)/500.0 ) + Vec2( instance.GetMouseX(), instance.GetMouseY() );
		AddObject((int)objPos.x, (int)objPos.y);
	}

	Camera::Update(dt);

	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Update(dt);
	}

	for(unsigned int i = 0; i < objectArray.size();i++){// exclui tudo
		if(objectArray[i]->IsDead()){
			Sound *sound = (Sound*) objectArray[i].get()->GetComponent("Sound");
			objectArray[i]->RemoveComponent(objectArray[i]->GetComponent("Sprite"));
			objectArray[i]->RemoveComponent(objectArray[i]->GetComponent("Face"));
			
			 if(sound == nullptr){
				objectArray.erase(objectArray.begin()+i);
			}
		}
	}
}

void State :: Render(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Render();
	}
}

bool State :: QuitRequested(){
	return quitRequested;
}

void State :: AddObject(int mouseX, int mouseY){
	GameObject *go = new GameObject();

	Sprite *img = new Sprite(*go,"img/penguinface.png");
	go->AddComponent(img);
	go->box.x = mouseX - go->box.w/2 + Camera::pos.x;
	go->box.y = mouseY - go->box.y/2 + Camera::pos.y;
	go->box.h = img->GetHeight();
	go->box.w = img->GetWidth();

	Sound* sound = new Sound(*go, "audio/boom.wav");
	go->AddComponent(sound);

	Face *face = new Face(*go);
	go->AddComponent(face);
	objectArray.emplace_back(go);
}