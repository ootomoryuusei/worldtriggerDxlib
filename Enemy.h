#pragma once
#include "Object3D.h"

class CsvReader;
class CharacterGroup;
class Tile;

class Enemy :
    public Object3D
{
public:
	Enemy(GameObject* parent);
	~Enemy();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	CsvReader* csv_;
	CharacterGroup* pCharacters_;
	Tile* pTile_;
};

