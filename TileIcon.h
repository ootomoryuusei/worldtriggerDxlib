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

	void SetSelect(bool _select) { select = _select; }
private:
	TILEDATA tile_;

	bool select;

	int hImage;
};

