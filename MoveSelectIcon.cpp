#include "MoveSelectIcon.h"
#include"Player1.h"

MoveSelectIcon::MoveSelectIcon(GameObject* parent) : Icon(parent)
{
	Load("Assets/Image/moveTypesIcon.png");
	position = { 100, 0, 0 };
	canVisible_ = false;
	fontHandle_ = -1;
	iconName = "行動タイプ";
}

MoveSelectIcon::~MoveSelectIcon()
{
}

void MoveSelectIcon::Update()
{
	if (canVisible_) {
		XMFLOAT2 graphSize = { GetGraphSizeF_2D().x,GetGraphSizeF_2D().y };
		XMFLOAT2 strSize = { (float)GetFontSizeToHandle(fontHandle_) * iconName.size() / 2,(float)GetFontSizeToHandle(fontHandle_) };
		space = { (graphSize.x - strSize.x) / 2,(graphSize.y / 2 - strSize.y) / 2 };

		Player1* pPl1 = GetParent()->GetParent()->FindGameObject<Player1>();
		XMFLOAT2 mousePos = pPl1->GetMousePos();

		if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y })) {
			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
				
				XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
				position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
				
			}
			prevMousePos_ = mousePos;
		}
	}
}

void MoveSelectIcon::Draw()
{
	if (canVisible_) {
		DrawGraph(position.x, position.y, hModel, TRUE);
		VECTOR fontPos = { position.x + space.x, position.y + space.y,position.z };
		DrawStringToHandle(fontPos.x, fontPos.y, iconName.c_str(), GetColor(0, 0, 0), fontHandle_);
		DrawLineAA(position.x, position.y + GetGraphSizeF_2D().y / 2
			, position.x + GetGraphSizeF_2D().x, position.y + GetGraphSizeF_2D().y / 2, GetColor(0, 0, 0), 2.0);
#if 1
		DrawBoxAA(position.x, position.y, position.x + GetGraphSizeF_2D().x, position.y + GetGraphSizeF_2D().y, GetColor(255, 0, 0), FALSE);
#endif
	}
}
