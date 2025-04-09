#pragma once
#include "Engine/GameObject.h"
#include"MoveTypesIcon.h"
#include<vector>

using std::vector;

class MoveTypesIcons :
    public GameObject
{
public:
	MoveTypesIcons(GameObject* parent);
	~MoveTypesIcons();
	void Update() override;
	void Draw() override;

	auto GetpMoveTypesIcons() { return pMoveTypesIcons_; }
private:
	vector<MoveTypesIcon*> pMoveTypesIcons_;
};

