#pragma once
#include "Engine/GameObject.h"
#include"TileIcon.h"
#include"GroupManager.h"
#include<vector>

class Map;

using std::vector;

class TileIcons :
    public GameObject
{
public:
	TileIcons(GameObject* parent);
	~TileIcons();
	void Initialize() override;
	void Update() override;
	auto GetpTIcon() { return pTIcons_; }
private:
	vector<TileIcon*> pTIcons_;
	Map* pMap;
	GroupManager* pGroupManager_;
};

