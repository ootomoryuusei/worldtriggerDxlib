#pragma once
#include "Icon.h"

class TileIcons;

class Map :
    public Icon
{
public:
	Map(GameObject* parent);
	~Map();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	XMFLOAT2 GetBoxSize(int _num) { return boxSize[_num]; }
	XMFLOAT2 GetBoxPos(int _num) { return boxPos[_num]; }

	const auto& GetpTileIcons()const { return pTileIcons_; }
private:
	XMFLOAT2 boxPos[2];
	XMFLOAT2 boxSize[2];

	TileIcons* pTileIcons_;
};

