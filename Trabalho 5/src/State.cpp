#include "../include/State.h"

State :: State(){
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

	GameObject *aliengo = new GameObject();
	aliengo->box.x = 512 - aliengo->box.h; //seta ele no centro do box
	aliengo->box.y = 300 - aliengo->box.w;
	Alien *alien = new Alien(*aliengo, 5);
	aliengo->AddComponent(alien);	
	//CameraFollower *camfow2 = new CameraFollower(*aliengo);
	//aliengo->AddComponent(camfow2);
	Camera::Follow(aliengo);
	objectArray.emplace_back(aliengo);

	music = new Music("audio/stageState.ogg");
	music->Play();

	quitRequested = false;
	started = false;		//inicializa com false no construtor
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

	Camera::Update(dt);

	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Update(dt);
	}
	for( int i = objectArray.size()-1; i >=0 ; i--){
		if(objectArray[i]->IsDead()){
			objectArray.erase(objectArray.begin()+i);
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

void State :: Start(){
	LoadAssets();

	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Start();
	}

	started = true;
}

std::weak_ptr<GameObject> State :: AddObject(GameObject *go){
	std::shared_ptr<GameObject> shared(go);
	
	objectArray.push_back(shared);

	if(started){
		shared->Start();		
	}
	std::weak_ptr<GameObject> weak(shared);
	return weak;
		
}


std::weak_ptr<GameObject> State :: GetObjectPtr(GameObject *go){

	for(unsigned int i = 0; i < objectArray.size(); i++){
		if(objectArray[i].get() == go){
			weak_ptr<GameObject> weak(objectArray[i]);
			return weak;
		}
	}

	return {};
}