#include "../include/StageState.h"
#include "../include/Game.h"
#include "../include/EndState.h"

StageState::StageState(){
	BackgroundMusic = nullptr;
    tileSet = nullptr;
    quitRequested = false;
    started = false;
    GameData::playerVictory = false;

}
void StageState::Start(){
    LoadAssets();
    for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void StageState::LoadAssets(){
    GameObject *go = new GameObject();

	GameObject *oceano = new GameObject();
	Sprite *bg = new Sprite(*oceano,"img/ocean.jpg");
	oceano->AddComponent(bg);
	CameraFollower *camfow = new CameraFollower(*oceano);
	oceano->AddComponent(camfow);
	oceano->box.x = Camera::pos.x;
	oceano->box.y = Camera::pos.y;
	oceano->box.w = bg->GetWidth();
	oceano->box.h = bg->GetHeight();
	objectArray.emplace_back(oceano);

	TileSet *tileset = new TileSet(64,64,"img/tileset.png");

	TileMap *tilemap = new TileMap(*go,"map/tileMap.txt", tileset);
	go->AddComponent(tilemap);
	go->box.x = 0;
	go->box.y = 0;
	objectArray.emplace_back(go);

    BackgroundMusic = new Music("audio/stageState.ogg");

    for(int i = 0; i < 3; i++){
        GameObject *aliengo = new GameObject();
        aliengo->box.x = rand()%1200 - aliengo->box.h/2; //seta ele no centro do box
        aliengo->box.y = rand()%1300 - aliengo->box.w;
        Alien *alien = new Alien(*aliengo, 5, rand()%3+1);
        aliengo->AddComponent(alien);	        
        objectArray.emplace_back(aliengo);
    }

	//Trabalho 6
	GameObject *penguingo = new GameObject();
	penguingo->box.x = 640 - penguingo->box.w/2;
	penguingo->box.y = 704 - penguingo->box.h/2;
	PenguinsBody *penguin = new PenguinsBody(*penguingo);
	penguingo->AddComponent(penguin);
	Camera::Follow(penguingo);

    objectArray.emplace_back(penguingo);

    BackgroundMusic->Play();
    Alien::canMove = false;
}

void StageState::Render(){
	for(unsigned int i = 0 ; i < objectArray.size();i++){
        objectArray[i] -> Render();
    }
}

void StageState::Update(float dt){
    if(PenguinsBody::player == nullptr){
        GameData::playerVictory = false;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }
    else if(Alien::aliencount <= 0){
        GameData::playerVictory = true;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }
    else{
        InputManager instance = InputManager::GetInstance();
        if(instance.KeyPress(ESCAPE_KEY) || instance.Quitresquested()) {
            popRequested = true;
            BackgroundMusic->Stop();
            Camera::Unfollow();
            Camera::pos = Vec2(0,0);
        }
        Camera::Update(dt);
        for(unsigned int i = 0 ; i < objectArray.size();i++){
            objectArray[i] -> Update(dt);
        }
        for(unsigned int i = 0 ; i < objectArray.size();i++){
            Collider *collider = (Collider *)objectArray[i] -> GetComponent("Collider");
            if(collider == nullptr)
                continue;
            for (unsigned int j = i+1; j < objectArray.size(); j++){
                Collider *collider2 = (Collider *)objectArray[j] -> GetComponent("Collider");
                if(collider2 == nullptr)
                    continue;
                if(collider ->IsColliding(*collider2)){
                    objectArray[i] ->NotifyCollision(*objectArray[j]);
                    objectArray[j] ->NotifyCollision(*objectArray[i]);
                }
            }
        }
        
        for(unsigned int i = 0, j = objectArray.size() ; i < j;i++){
            if(objectArray[i] -> IsDead()){
                objectArray.erase(objectArray.begin()+i);
                i--;
                j--;
            }
        }
        Alien::canMove = true;
    }
    

}
StageState::~StageState(){
    objectArray.clear();
}
void StageState::Resume() {

}

void StageState::Pause() {
}