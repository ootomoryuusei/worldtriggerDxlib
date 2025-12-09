#include "TileIcon.h"
#include"Mouse.h"
#include"MoveTypeIcons.h"
#include"MoveSelectIcon.h"
#include"UnitIcons.h"

TileIcon::TileIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//tile.png");
	position = {0, 0, 0 };
	tile_.pos = { 0,0,0 };
	tile_.num = -1;
	select = false;
	selected = false;
	hImage = LoadGraph("Assets//Image//OnTile.png");
}

TileIcon::~TileIcon()
{
}

void TileIcon::Initialize()
{
	
}

void TileIcon::Update()
{
	pMoveSelectIcon_ = GetParent()->GetParent()->GetParent()->FindGameObject<MoveSelectIcon>();
	position = tile_.pos;

	if (select) {
		Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();

		int num = 0;
		if (IsInMousePoint(mousePos)) {
			if (pMouse->IsDoubleClicked(Mouse::LEFT)) {
				const auto& ptr = pMoveSelectIcon_->GetpMoveTypeIcons();
				const auto& pUnitIcons = GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
				auto& pMoveSetIcon = pUnitIcons->GetpMoveSetIcon();
				string name = ptr->GetpSelectTypeIcon()->GetIconName();
				pUnitIcons->GetpSelecting_ptr()->AddMoveMent(tile_.offset,name);
				select = false;
				selected = true;
			}
		}
	}
	center_pos.x = graphSizeF_.halfX();
	center_pos.y = graphSizeF_.halfY();
	angle = 0;
}

void TileIcon::Draw()
{
	string num = std::to_string(tile_.num);
	DrawRotaGraph3(position.x + graphSizeF_.halfX(), position.y + graphSizeF_.halfY(), center_pos.x, center_pos.y, scale_.x, scale_.y, angle, hModel, TRUE, FALSE);
	if (select) {
		DrawGraph(position.x, position.y, hImage, TRUE);
	}
#if 0
		DrawString(position.x + graphSizeF_.halfX / 2, position.y + graphSizeF_.halfY / 2, num.c_str(), GetColor(255, 255, 255));
		DrawBoxAA(position.x + graphSizeF_.x/4, position.y, position.x + (graphSizeF_.x/4 * 3), position.y + graphSizeF_.y, GetColor(255, 255, 255), FALSE);
#endif
}
