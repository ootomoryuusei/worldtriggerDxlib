#pragma once
#include "Icon.h"

class TileIcons;

class MoveMentsLoad :
    public Icon
{
public:
	MoveMentsLoad(GameObject* parent);
	~MoveMentsLoad();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void setMoveMent(vector<FLOAT3> _movement) { movement_ = _movement; }
private:
	void DrawMoveLine();
	vector<FLOAT3> movement_;
	TileIcons* pTileIcons_;
};

