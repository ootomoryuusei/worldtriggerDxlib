#pragma once
#include "TypedGroup.h"
#include"Character.h"
#include<vector>

using std::vector;

class Tile;

class CharacterGroup :
    public TypedGroup<Character>
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

