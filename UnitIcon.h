#pragma once
#include "Icon.h"
#include<vector>

class Mouse;
class TileIcons;
class MoveSetIcons;
class MoveSelectIcons;
class MoveTypesIcons;

using std::vector;

class UnitIcon :
    public Icon
{
public:
	UnitIcon(GameObject* parent);
	~UnitIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	const auto& GetMoveMent() const{ return moveMent; }
	void SetMoveMent(int _moveMent) { moveMent.push_back(_moveMent); }
private:

	vector<int> moveMent;

	Mouse* pMouse_;
	TileIcons* pTileIcons_;
	MoveSetIcons* pMoveSetIcons_;
	MoveSelectIcons* pMoveSelectIcons_;
	MoveTypesIcons* pMoveTypesIcons_;
};

