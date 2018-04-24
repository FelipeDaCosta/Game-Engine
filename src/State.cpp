#include "../include/State.h"

const float PI = 3.141592643589;

State::State() : music("./assets/audio/stageState.ogg"){
	GameObject *go_sprite = new GameObject();
	go_sprite->AddComponent(new Sprite(*go_sprite, "./assets/img/ocean.jpg"));
	objectArray.emplace_back(go_sprite);

	GameObject *go_map = new GameObject();
	TileSet *tileSet = new TileSet(*go_map, 64, 64, "./assets/img/tileset.png"); 
	TileMap *tileMap = new TileMap(*go_map, "./assets/map/tileMap.txt", tileSet);
	go_map->AddComponent(tileMap);
	go_map->box.SetPosition(0, 0);
	objectArray.emplace_back(go_map);

	quitRequested = false;
    music.Play(-1);
}

State::~State() {
    objectArray.clear();
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
				// chamar funções de GameObjects, use objectArray[i]->função() direto.
				if(go->box.Contains((float)mouseX, (float)mouseY ) ) {
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
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ).Sum(Vec2( mouseX, mouseY));
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::LoadAssets() {
   
}

void State::Update(float dt) {
	if(quitRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		int mouseX = InputManager::GetInstance().GetMouseX();
		int mouseY = InputManager::GetInstance().GetMouseY();
		Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ).Sum(Vec2(mouseX, mouseY));
		AddObject((int)objPos.x, (int)objPos.y);
	}
    for(unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}

void State::Render() {
    for(unsigned int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject* go = new GameObject();
	go->box.SetPosition((float) mouseX,(float) mouseY);
    go->AddComponent(new Sprite(*go, "./assets/img/penguinface.png"));
    go->AddComponent(new Sound(*go, "./assets/audio/boom.wav"));
	go->AddComponent(new Face(*go));
    objectArray.emplace_back(go);
}

bool State::QuitRequested() {
    return quitRequested;
}

