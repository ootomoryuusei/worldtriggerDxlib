#pragma once
#include "Engine/GameObject.h"

class SetScene :
    public GameObject
{
public:
	SetScene(GameObject* parent);
	~SetScene();
	void Update() override;
	void Draw() override;
private:

};

