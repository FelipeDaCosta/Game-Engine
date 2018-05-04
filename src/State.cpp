#include "../include/State.h"

const float PI = 3.141592643589;

GameObject* AddFace(int mouseX, int mouseY) {
    GameObject* go = new GameObject();
	go->box.SetPosition((float) mouseX + Camera::pos.x,(float) mouseY + Camera::pos.y);
    go->AddComponent(new Sprite(*go, "./assets/img/penguinface.png"));
    go->AddComponent(new Sound(*go, "./assets/audio/boom.wav"));
	go->AddComponent(new Face(*go));
	return go;
}

State::State() : music("./assets/audio/stageState.ogg"), started(false) {
	GameObject *go_sprite = new GameObject();
	go_sprite->AddComponent(new Sprite(*go_sprite, "./assets/img/ocean.jpg"));
	go_sprite->AddComponent(new CameraFollower(*go_sprite));
	objectArray.emplace_back(go_sprite);

	GameObject *go_map = new GameObject();
	TileSet *tileSet = new TileSet(*go_map, 64, 64, "./assets/img/tileset.png"); 
	TileMap *tileMap = new TileMap(*go_map, "./assets/map/tileMap.txt", tileSet);
	go_map->AddComponent(tileMap);
	go_map->box.SetPosition(0, 0);
	objectArray.emplace_back(go_map);

	GameObject * go_alien = new GameObject();
	go_alien->AddComponent(new Alien(*go_alien, 10));
	go_alien->box.SetPosition(512, 300);
	objectArray.emplace_back(go_alien);

	quitRequested = false;
    music.Play(-1);
}

State::~State() {
    objectArray.clear();
}

void State::Start() {
	LoadAssets();
	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void State::LoadAssets() {
   
}

void State::Update(float dt) {
	if(quitRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
	Camera::Update(dt);
	if(InputManager::GetInstance().KeyPress(SPACE_KEY)) {
		int mouseX = InputManager::GetInstance().GetMouseX();
		int mouseY = InputManager::GetInstance().GetMouseY();
		Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ).Sum(Vec2(mouseX, mouseY));
		AddObject(AddFace(mouseX, mouseY));
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

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	std::shared_ptr<GameObject> goPtr(go);
	objectArray.push_back(goPtr);
	if(started) {
		goPtr->Start();
	}
	std::weak_ptr<GameObject> returnPtr(goPtr);
	return returnPtr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	std::weak_ptr<GameObject> returnPtr;
	for(int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i].get() == go) {
			returnPtr = objectArray[i];
		}
	}
	return returnPtr;
}

bool State::QuitRequested() {
    return quitRequested;
}

