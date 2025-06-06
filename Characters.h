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

	const auto& GetpCharacters() const { return pCharacters_; }

private:
	vector<Character*> pCharacters_;

	Tile* pTile_;

	void CreateCharInstance(int _char_num);

	enum CHARACTERS {
		MIKUMO_OSAMU = 1,
		AMATORI_CHIKA,
		KUGA_YUUMA
	};
};

