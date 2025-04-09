#include "UnitIcon.h"
#include"Player1.h"
#include"TileIcons.h"
#include"MoveSetIcons.h"
#include"MoveTypesIcons.h"

UnitIcon::UnitIcon(GameObject* parent) : Icon(parent)
{
	/*Load("Assets//Image//tile.png");*/
	/*position = { 1000, 20, 0 };*/
	canVisible_ = true;
	/*position = tile_.position;*/
	doubleClicked = false;
	lastClickTime = 0;
	doubleClickTime = 200;
	prevMouse = false;
	currentMouse = false;
	now = 0;

	createNum_ = -1;
}

UnitIcon::~UnitIcon()
{
}

void UnitIcon::Update()
{
	Player1* pPl1 = GetParent()->GetParent()->FindGameObject<Player1>();
	XMFLOAT2 mousePos = pPl1->GetMousePos();
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();

	prevMouse = currentMouse;
	currentMouse = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y })) {
		if (currentMouse) {
			XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
			position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
		}
		else {
			for (auto itr : pTileIcons->GetpTIcon()) {
				XMFLOAT2 leftUp = { itr->Get3DPosition().x + itr->GetGraphSizeF_2D().x / 4, itr->Get3DPosition().y };
				XMFLOAT2 graphSize = { itr->GetGraphSizeF_2D().x / 4 * 2, itr->GetGraphSizeF_2D().y };
				if (PointInBox({ position.x, position.y }, leftUp, graphSize)) {
					position = { itr->Get3DPosition() };
				}
			}
		}

		if (currentMouse && !prevMouse) { //ダブルクリックの処理
			MoveSetIcons* pMoveSetIcons = GetParent()->GetParent()->FindGameObject<MoveSetIcons>();
			MoveTypesIcons* pMoveTypesIcons = GetParent()->GetParent()->FindGameObject<MoveTypesIcons>();
			now = GetNowCount();
			if (now - lastClickTime <= doubleClickTime) { //ダブルクリックした
				pMoveSetIcons->GetpMoveSetIcons()[createNum_]->SetCanVisible(true);
				pMoveTypesIcons->GetpMoveTypesIcons()[createNum_]->SetCanVisible(true);
			}
			else { //シングルクリック
				lastClickTime = now;
				pMoveSetIcons->GetpMoveSetIcons()[createNum_]->SetCanVisible(false);
				pMoveTypesIcons->GetpMoveTypesIcons()[createNum_]->SetCanVisible(false);
			}
		}
		prevMousePos_ = mousePos;
	}
}

void UnitIcon::Draw()
{
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();
	XMFLOAT2 TileSize = { pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().x,pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().y };
	if (canVisible_) {
		DrawGraph(position.x + (TileSize.x/2 - GetGraphSizeF_2D().halfX), position.y + (TileSize.y/2 - GetGraphSizeF_2D().halfY), hModel, TRUE);
#if 1
		DrawBoxAA(position.x, position.y, position.x + GetGraphSizeF_2D().x , position.y + GetGraphSizeF_2D().y, GetColor(255, 0, 0), FALSE);
#endif
	}
}
