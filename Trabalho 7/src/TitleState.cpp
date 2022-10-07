#include "../include/TitleState.h"
#include "../include/StageState.h"
#include "../include/Game.h"

TitleState::TitleState(){
    GameObject *go = new GameObject();
    Sprite *title = new Sprite(*go, "img/title.jpg");
    go->box.x = go->box.y = 0;
    go ->AddComponent(title);
    objectArray.emplace_back(go);
    GameObject *goText = new GameObject();
    SDL_Color color = {0,0,0,255};
    Text *text = new Text(*goText,"font/Call me maybe.ttf",20,Text::BLENDED,"Pressione espaco para iniciar", color,0.5);
    goText -> AddComponent(text);
    objectArray.emplace_back(goText);
    goText-> box.x = 405;
    goText-> box.y = 500;
}

void TitleState::Start(){

}

void TitleState::LoadAssets(){

}

void TitleState::Render(){
    Camera::pos = Vec2(0,0);
    RenderArray();
}

void TitleState::Update(float dt){
    
	InputManager instance = InputManager::GetInstance();
	if(instance.KeyPress(ESCAPE_KEY) || instance.QuitRequested())
		quitRequested = true;
    if(instance.KeyPress(SPACEBAR)){
        Game::GetInstance().Push(new StageState());
    }
    UpdateArray(dt);


}
TitleState::~TitleState(){
    objectArray.clear();
}

void TitleState::Resume() {

}

void TitleState::Pause() {
}