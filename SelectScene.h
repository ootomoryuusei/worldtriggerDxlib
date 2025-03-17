#pragma once
#include "Engine/GameObject.h"
#include"CharacterIcon.h"
#include"Engine/CsvReader.h"
#include<vector>


using std::vector;
using std::string;

class SelectScene :
    public GameObject
{
public:
	SelectScene(GameObject* parent);
	~SelectScene();
	void Update() override;
	void Draw() override;
private:
};

