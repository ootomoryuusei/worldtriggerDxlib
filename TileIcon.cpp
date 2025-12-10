#include "TileIcon.h"
#include"Mouse.h"
#include"MoveTypeIcons.h"
#include"MoveSelectIcon.h"
#include"UnitIcons.h"

TileIcon::TileIcon(GameObject* parent) : Object2D(parent)
{
	LoadSprite("Assets//Image//tile.png");
	transform_.position_ = {0, 0, 0 };
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
	transform_.position_ = { tile_.pos.x,tile_.pos.y,tile_.pos.z };

	pivot_.x = graphSizeF_.halfX();
	pivot_.y = graphSizeF_.halfY();
	angle_ = 0;
	Object2D::Update();
}

void TileIcon::Draw()
{
	string num = std::to_string(tile_.num);
	DrawRotaGraph3(position_.x + pivot_.x, position_.y + pivot_.y, pivot_.x, pivot_.y, scale_.x, scale_.y, angle_, hModel_, TRUE, FALSE);
	if (select) {
		DrawGraph(position_.x, position_.y, hImage, TRUE);
	}
#if 0
		DrawString(position.x + graphSizeF_.halfX / 2, position.y + graphSizeF_.halfY / 2, num.c_str(), GetColor(255, 255, 255));
		DrawBoxAA(position.x + graphSizeF_.x/4, position.y, position.x + (graphSizeF_.x/4 * 3), position.y + graphSizeF_.y, GetColor(255, 255, 255), FALSE);
#endif
}

void TileIcon::DeviceEvent(const DoubleClickEvent& event)
{
	switch (event.button)
	{
	case LEFT:
		if (!select) return;
		const auto& ptr = pMoveSelectIcon_->GetpMoveTypeIcons();
		const auto& pUnitIcons = GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
		auto& pMoveSetIcon = pUnitIcons->GetpMoveSetIcon();
		string name = "";
		name = ptr->GetpSelectTypeIcon()->GetIconName();
		pUnitIcons->GetpSelecting_ptr()->AddMoveMent(tile_.offset, name);
		select = false;
		selected = true;
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}
