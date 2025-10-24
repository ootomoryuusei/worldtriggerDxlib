#pragma once
#include "Icon.h"

class MoveSelectIcon;

class TileIcon :
    public Icon
{
public:
	TileIcon(GameObject* parent);
	~TileIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetTileData(TILEDATA _tile) { tile_ = _tile; }
	TILEDATA GetTileData() { return tile_; }

	void SetSelect(bool _select) { select = _select; }
	void SetSelected(bool _selected) { selected = _selected; }
	bool GetSelected() { return selected; }
private:
	TILEDATA tile_;

	bool select;
	bool selected;

	int hImage;

	MoveSelectIcon* pMoveSelectIcon_;
};

