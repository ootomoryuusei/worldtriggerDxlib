#include "TileIcon.h"
#include"Mouse.h"
#include"MoveTypesIcons.h"
#include"UnitIcons.h"


TileIcon::TileIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//tile.png");
	position = {0, 0, 0 };
	canVisible_ = true;
	tile_.position = { 0,0,0 };
	tile_.num = -1;
	select = false;
	selected = false;
	hImage = LoadGraph("Assets//Image//OnTile.png");
}

TileIcon::~TileIcon()
{
}

void TileIcon::Update()
{
	if (select) {
		Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();

		int num = 0;
		if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y })) {
			if (pMouse->IsDoubleClicked(Mouse::LEFT)) {
				MoveTypesIcons* pMoveTypesIcons = GetParent()->GetParent()->FindGameObject<MoveTypesIcons>();
				for (auto& itr : pMoveTypesIcons->GetpMoveTypesIcons()) {
					if (itr->GetCanVisible()) {
						num = itr->GetCreateNum();
					}
				}

				UnitIcons* pUnitIcons = GetParent()->GetParent()->FindGameObject<UnitIcons>();
				pUnitIcons->GetpUnitIcons()[num]->SetMoveMent(tile_.num);
				select = false;
				selected = true;
			}
		}
	}
	
}


void TileIcon::Draw()
{
	string num = std::to_string(tile_.num);
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
		if (select) {
			DrawGraph(position.x, position.y, hImage, TRUE);
		}
#if 0
		DrawString(position.x + graphSizeF_.halfX, position.y + graphSizeF_.halfY, num.c_str(), GetColor(255, 255, 255));
		DrawBoxAA(position.x + graphSizeF_.x/4, position.y, position.x + (graphSizeF_.x/4 * 3), position.y + graphSizeF_.y, GetColor(255, 255, 255), FALSE);
#endif
	}
}
