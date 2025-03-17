#pragma once
#include "Icon.h"
class TileIcon :
    public Icon
{
public:
	TileIcon(GameObject* parent);
	~TileIcon();
	void Update() override;
	void Draw() override;

	void SetTileData(TILEDATA _tile) { tile_ = _tile; }
	TILEDATA GetTileData() { return tile_; }
private:
	TILEDATA tile_;
};

