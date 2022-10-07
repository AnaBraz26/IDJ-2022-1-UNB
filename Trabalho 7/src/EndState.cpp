#include "../include/EndState.h"
#include "../include/StageState.h"
#include "../include/TitleState.h"
#include "../include/Game.h"
#include "../include/PenguinsBody.h"

EndState::EndState(){
    Camera::pos = Vec2(0,0);
    if(GameData::playerVictory){

        GameObject *go = new GameObject();
        Sprite *title = new Sprite(*go, "img/win.jpg");
        go ->AddComponent(title);
        objectArray.emplace_back(go);
        go->box.x = go->box.y = 0;
        GameObject *goText = new GameObject();
        SDL_Color color = {0,0,0,255};
        Text *text = new Text(*goText,"font/Call me maybe.ttf",20,Text::BLENDED,"Pressione espaco para voltar ao Menu ou ESC para sair", color,0.5);
        goText -> AddComponent(text);
        objectArray.emplace_back(goText);
        goText-> box.x = 300;
        goText-> box.y = 500;
        backgroundMusic = new Music("audio/endStateWin.ogg");
        
        backgroundMusic -> Play();

    }
    else{
        if(PenguinsBody::player == nullptr){
            GameObject *go = new GameObject();
            Sprite *title = new Sprite(*go, "img/lose.jpg");
            go->box.x = go->box.y = 0;
            go ->AddComponent(title);
            objectArray.emplace_back(go);
            GameObject *goText = new GameObject();
            SDL_Color color = {0,0,0,255};
            Text *text = new Text(*goText,"font/Call me maybe.ttf",20,Text::BLENDED,"Pressione espaco para voltar ao Menu ou ESC para sair", color,0.5);
            goText -> AddComponent(text);
            objectArray.emplace_back(goText);
            goText-> box.x = 300;
            goText-> box.y = 550;
            backgroundMusic = new Music("audio/endStateLose.ogg");
            backgroundMusic -> Play();
        }
    }
}
void EndState::Start(){
}

void EndState::LoadAssets(){
}
void EndState::Render(){
    Camera::pos = Vec2(0,0);
    RenderArray();
}
void EndState::Update(float dt){
    
	InputManager instance = InputManager::GetInstance();
	if(instance.KeyPress(ESCAPE_KEY) || instance.Quitresquested() )
		quitRequested = true;
    if(instance.KeyPress(SPACEBAR)){
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
    UpdateArray(dt);


}
EndState::~EndState(){
    objectArray.clear();
    backgroundMusic->Stop();
}
void EndState::Resume() {

}

void EndState::Pause() {
}