#include "TileIcon.h"
#include"Mouse.h"

TileIcon::TileIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//tile.png");
	position = {0, 0, 0 };
	canVisible_ = true;
	tile_.position = { 0,0,0 };
	tile_.num = -1;
}

TileIcon::~TileIcon()
{
}

void TileIcon::Update()
{
	Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();

	if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y})) {
		if (pMouse->IsDoubleClicked(Mouse::LEFT)) {
		}
		prevMousePos_ = mousePos;
	}
}


void TileIcon::Draw()
{
	string num = std::to_string(tile_.num);
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
#if 1
		DrawString(position.x + GetGraphSizeF_2D().halfX, position.y + GetGraphSizeF_2D().halfY, num.c_str(), GetColor(255, 255, 255));
		DrawBoxAA(position.x + GetGraphSizeF_2D().x/4, position.y, position.x + (GetGraphSizeF_2D().x/4 * 3), position.y + GetGraphSizeF_2D().y, GetColor(255, 255, 255), FALSE);
#endif
	}
}
