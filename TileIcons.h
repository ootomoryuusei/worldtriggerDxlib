#pragma once
#include "Engine/GameObject.h"
#include"TileIcon.h"
#include<vector>

using std::vector;

class TileIcons :
    public GameObject
{
public:
	TileIcons(GameObject* parent);
	~TileIcons();
	void Update() override;

	auto GetpTIcon() { return pTIcons_; }
private:
	vector<TileIcon*> pTIcons_;
};

