#pragma once
#include "Engine/GameObject.h"
#include"MoveSelectIcon.h"
#include<vector>

using std::vector;

class MoveSelectIcons :
    public GameObject
{
public:
	MoveSelectIcons(GameObject* parent);
	~MoveSelectIcons();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	auto GetpMoveSelectIcons() { return pMoveSelectIcons_; }
private:
	vector<MoveSelectIcon*> pMoveSelectIcons_;
};

