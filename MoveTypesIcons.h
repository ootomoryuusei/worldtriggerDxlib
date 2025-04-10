#pragma once
#include "Engine/GameObject.h"
#include"MoveTypeIcons.h"

class MoveTypesIcons :
    public GameObject
{
public:
	MoveTypesIcons(GameObject* parent);
	~MoveTypesIcons();
	void Update() override;

	auto GetpMoveTypesIcons() { return pMoveTypesIcons_; }
private:
	vector<MoveTypeIcons*> pMoveTypesIcons_;
};

