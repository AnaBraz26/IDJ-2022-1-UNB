#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/State.h"

State :: State(){
	GameObject *go = new GameObject();
	Sprite *bg = new Sprite(*go,"img/ocean.jpg");

	go->AddComponent(bg);
	go->box.x = 0;
	go->box.y = 0;
	objectArray.emplace_back(go);

	music = new Music("audio/stageState.ogg");

	quitRequested = false;
	music->Play();
}

State :: ~State(){
	objectArray.clear();
}

void State :: LoadAssets(){

}

void State :: Update(float dt){
	Input();
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

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->>função() direto.

				if(go->box.Is( Vec2(mouseX, mouseY) )) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).rotate( -50 + 50*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State :: AddObject(int mouseX, int mouseY){
	GameObject *go = new GameObject();

	Sprite *img = new Sprite(*go,"img/penguinface.png");
	go->AddComponent(img);
	go->box.x = mouseX - go->box.center().x;
	go->box.y = mouseY - go->box.center().y;

	Sound* sound = new Sound(*go, "audio/boom.wav");
	go->AddComponent(sound);

	Face *face = new Face(*go);
	go->AddComponent(face);
	objectArray.emplace_back(go);
}