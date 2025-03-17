#include "UnitIcon.h"
#include"Player1.h"

UnitIcon::UnitIcon(GameObject* parent) : Icon(parent)
{
	/*Load("Assets//Image//tile.png");*/
	/*position = { 1000, 20, 0 };*/
	canVisible_ = true;
	/*position = tile_.position;*/
}

UnitIcon::~UnitIcon()
{
}

void UnitIcon::Update()
{
	Player1* pPl1 = GetParent()->GetParent()->FindGameObject<Player1>();
	XMFLOAT2 mousePos = pPl1->GetMousePos();
	if (PointInBox(mousePos, { position.x,position.y }, { graphSizeF_.x,graphSizeF_.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {

		}
	}
}

//void UnitIcon::Draw()
//{
//}
