#include "../include/State.h"

State :: State(){
	quitRequested = false;
	started = false;		//inicializa com false no construtor
	popRequested = false;
}

State :: ~State(){
	objectArray.clear();
}

void State :: LoadAssets(){

}

void State :: RenderArray(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Render();
	}
}

bool State :: QuitRequested(){
	return quitRequested;
}

bool State::PopRequested(){
	return popRequested;
}

void State:: StartArray(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Start();
	}
}

void State::UpdateArray (float dt){
    for(unsigned int i = 0; i < objectArray.size();i++){
        objectArray[i] -> Update(dt);
    }
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

