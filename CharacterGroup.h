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

	/*const auto& GetpCharacters() const { return pCharacters_; }

	void AddCharacter(Character* _pCharacter) { pCharacters_.push_back(_pCharacter); }*/

private:
	/*vector<Character*> pCharacters_;*/

	Tile* pTile_;
};

