#pragma once
#include "Engine/GameObject.h"
#include"MoveSetIcon.h"
#include<vector>

using std::vector;

class MoveSetIcons :
    public GameObject
{
public:
	MoveSetIcons(GameObject* parent);
	~MoveSetIcons();
	void Update() override;

	auto GetpMoveSetIcons() { return pMoveSetIcons_; }
private:
	vector<MoveSetIcon*> pMoveSetIcons_;
};

