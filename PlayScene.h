#pragma once
#include "Engine/GameObject.h"

class PlayScene : public GameObject
{
public:
	PlayScene(GameObject* parent);
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
};
