#pragma once
#include "Object3D.h"
#include"Character.h"
#include<vector>

using std::vector;

class Tile;

class CharacterGroup :
    public Object3D
{
public:
	CharacterGroup(GameObject* parent);
	~CharacterGroup();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	Tile* pTile_;
};

