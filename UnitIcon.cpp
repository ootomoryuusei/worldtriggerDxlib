#include "UnitIcon.h"
#include"Player1.h"
#include"TileIcons.h"
#include"MoveSetIcons.h"
#include"MoveSelectIcons.h"
#include"MoveTypesIcons.h"
#include "Mouse.h"

UnitIcon::UnitIcon(GameObject* parent) : Icon(parent)
{
	canVisible_ = true;

	createNum_ = -1;

	/*firstSet = false;*/
}

UnitIcon::~UnitIcon()
{
}

void UnitIcon::Initialize()
{
}

void UnitIcon::Update()
{
	Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();

	MoveSetIcons* pMoveSetIcons = GetParent()->GetParent()->FindGameObject<MoveSetIcons>();
	MoveSelectIcons* pMoveSelectIcons = GetParent()->GetParent()->FindGameObject<MoveSelectIcons>();
	MoveTypesIcons* pMoveTypesIcons = GetParent()->GetParent()->FindGameObject<MoveTypesIcons>();

	
	if (PointInBox(mousePos, { position.x, position.y }, { graphSizeF_.x, graphSizeF_.y })) {

		//unitIconの移動処理
		if (pMouse->IsPressed(Mouse::LEFT)) {
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

		//unitIconの選択処理
		if (pMouse->IsDoubleClicked(Mouse::LEFT)) { //ダブルクリックの処理
			
			pMoveSetIcons->GetpMoveSetIcons()[createNum_]->SetCanVisible(true);
			pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->SetCanVisible(true);
			for (auto& itr : pMoveTypesIcons->GetpMoveTypesIcons()[createNum_]->GetpMoveTypeIcons()) {
				itr->SetCanVisible(true);
			}
		}
		else if (pMouse->IsClicked(Mouse::LEFT)) { //シングルクリック
			pMoveSetIcons->GetpMoveSetIcons()[createNum_]->SetCanVisible(false);
			pMoveSelectIcons->GetpMoveSelectIcons()[createNum_]->SetCanVisible(false);
			for (auto& itr : pMoveTypesIcons->GetpMoveTypesIcons()[createNum_]->GetpMoveTypeIcons()) {
				itr->SetCanVisible(false);
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
		DrawGraph(position.x + (TileSize.x/2 - graphSizeF_.halfX), position.y + (TileSize.y/2 - graphSizeF_.halfY), hModel, TRUE);
#if 1
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x , position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
	}
}
