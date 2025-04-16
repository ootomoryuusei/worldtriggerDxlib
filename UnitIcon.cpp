#include "UnitIcon.h"
#include"Player1.h"
#include"TileIcons.h"
#include"MoveSetIcons.h"
#include"MoveSelectIcons.h"
#include"MoveTypesIcons.h"

UnitIcon::UnitIcon(GameObject* parent) : Icon(parent)
{
	canVisible_ = true;
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
			for (auto itr : pTileIcons->GetpTIcon()) { //タイルとの当たり判定
				XMFLOAT2 leftUp = { itr->Get3DPosition().x + itr->GetGraphSizeF_2D().x / 4, itr->Get3DPosition().y };
				XMFLOAT2 graphSize = { itr->GetGraphSizeF_2D().x / 4 * 2, itr->GetGraphSizeF_2D().y };
				XMFLOAT2 graphCenter = { position.x + graphSizeF_.halfX,position.y + graphSizeF_.halfY };
				if (PointInBox({ graphCenter.x, graphCenter.y }, leftUp, graphSize)) { 
					position = { itr->Get3DPosition() };
				}
			}
		}

		if (currentMouse && !prevMouse) { //ダブルクリックの処理
			MoveSetIcons* pMoveSetIcons = GetParent()->GetParent()->FindGameObject<MoveSetIcons>();
			MoveSelectIcons* pMoveSelectIcons = GetParent()->GetParent()->FindGameObject<MoveSelectIcons>();
			MoveTypesIcons* pMoveTypesIcons = GetParent()->GetParent()->FindGameObject<MoveTypesIcons>();
			now = GetNowCount();
			if (now - lastClickTime <= doubleClickTime) { //ダブルクリックした
				pMoveSetIcons->GetpMoveSetIcons()[createNum_]->SetCanVisible(true);
				pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->SetCanVisible(true);
				for (auto& itr : pMoveTypesIcons->GetpMoveTypesIcons()[createNum_]->GetpMoveTypeIcons()) {
					itr->SetCanVisible(true);
				}
				
			}
			else { //シングルクリック
				lastClickTime = now;
				pMoveSetIcons->GetpMoveSetIcons()[createNum_]->SetCanVisible(false);
				pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->SetCanVisible(false);
				for (auto& itr : pMoveTypesIcons->GetpMoveTypesIcons()[createNum_]->GetpMoveTypeIcons()) {
					itr->SetCanVisible(false);
				}
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
