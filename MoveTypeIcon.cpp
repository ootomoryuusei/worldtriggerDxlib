#include "MoveTypeIcon.h"
#include"Player1.h"
#include"MoveSelectIcons.h"
#include"Mouse.h"

MoveTypeIcon::MoveTypeIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets//Image//MoveTypeButton.png");
	position = { 0, 0, 0 };
	canVisible_ = false;
	fontHandle_ = -1;
	iconName_ = "";
}

MoveTypeIcon::~MoveTypeIcon()
{
}

void MoveTypeIcon::Update()
{
	if (canVisible_) {
		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName_.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		space = { (graphSizeF_.x - strSize.x) / 2,(graphSizeF_.y- strSize.y) /2};

		Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
		XMFLOAT2 mousePos = pMouse->GetMousePos();

		if (pMouse->IsDoubleClicked(Mouse::LEFT)) {
			if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x,graphSizeF_.y })) {
				clicked = true;
			}
		}
		else {
			clicked = false;
		}
	}
}

void MoveTypeIcon::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
		VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
		DrawStringToHandle(fontPos.x, fontPos.y, iconName_.c_str(), GetColor(0, 0, 0), fontHandle_);
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x, position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
	}
}
