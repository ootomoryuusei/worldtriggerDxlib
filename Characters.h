#pragma once
#include "Object3D.h"
#include"Character.h"
#include<vector>

using std::vector;

class Tile;

class Characters :
    public Object3D
{
public:
	Characters(GameObject* parent);
	~Characters();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void CreateCharacterInstance(int _char_num);

	const auto& GetpCharacters() const { return pCharacters_; }

	void AddCharacter(Character* _pCharacter) { pCharacters_.push_back(_pCharacter); }

private:
	vector<Character*> pCharacters_;

	Tile* pTile_;

	enum CHARACTERS {
		MIKUMO_OSAMU = 1,
		AMATORI_CHIKA,
		KUGA_YUUMA
	};
};

