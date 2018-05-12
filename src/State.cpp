#include "../include/State.h"

const float PI = 3.141592643589;

PenguinBody *pbody = nullptr;

State::State() : music("./assets/audio/stageState.ogg"), started(false) {
	GameObject *go_sprite = new GameObject();
	go_sprite->AddComponent(new Sprite(*go_sprite, "./assets/img/ocean.jpg", 1, 1));
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

	GameObject *go_player = new GameObject();
	pbody = new PenguinBody(*go_player);
	go_player->AddComponent(pbody);
	go_player->box.SetPosition(0, 0);
	objectArray.emplace_back(go_player);

	Camera::Follow(go_player);

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
		pbody->hp = 0;
	}
    for(unsigned int i = 0; i < objectArray.size(); i++) {
		
        objectArray[i]->Update(dt);
        if(objectArray[i]->IsDead()) {
           objectArray.erase(objectArray.begin() + i);
        }

		// Collision
		for(unsigned int j = i+1; j < objectArray.size(); j++) {
			GameObject& go1 = *objectArray[i];
			GameObject& go2 = *objectArray[j];

			Collider* col1 = (Collider*) go1.GetComponent("Collider");
			Collider* col2 = (Collider*) go2.GetComponent("Collider");

			if(col1 != nullptr && col2 != nullptr) {
				if(Collision::IsColliding(col1->box, col2->box, go1.angleDeg, go2.angleDeg)) {
					objectArray[i]->NotifyCollision(*objectArray[j]);
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}
			}
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
	objectArray.emplace_back(goPtr);
	if(started) {
		goPtr->Start();
	}
	std::weak_ptr<GameObject> returnPtr(goPtr);
	return returnPtr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for(int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i].get() == go) {
			return std::weak_ptr<GameObject>(objectArray[i]);
		}
	}
	return std::weak_ptr<GameObject>();
}

bool State::QuitRequested() {
    return quitRequested;
}

