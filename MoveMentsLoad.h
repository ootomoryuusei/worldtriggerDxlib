#pragma once
#include "Object2D.h"

class TileIcons;
class GroupManager;

class MoveMentsLoad :
    public Object2D
{
public:
	MoveMentsLoad(GameObject* parent);
	~MoveMentsLoad();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void setMoveMent(vector<MOVEMENT> _movement) { movement_ = _movement; }
private:
	void DrawMoveLine();
	vector<MOVEMENT> movement_;
	GroupManager* pGroupManager_;
	TileIcons* pTileIcons_;
};

