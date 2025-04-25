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
}

UnitIcon::~UnitIcon()
{
}

void UnitIcon::Initialize()
{
	
}

void UnitIcon::Update()
{
	Mouse* pMouse_ = GetParent()->GetParent()->FindGameObject<Mouse>();
	TileIcons* pTileIcons_ = GetParent()->GetParent()->FindGameObject<TileIcons>();
	MoveSetIcons* pMoveSetIcons_ = GetParent()->GetParent()->FindGameObject<MoveSetIcons>();
	MoveSelectIcons* pMoveSelectIcons_ = GetParent()->GetParent()->FindGameObject<MoveSelectIcons>();
	MoveTypesIcons* pMoveTypesIcons_ = GetParent()->GetParent()->FindGameObject<MoveTypesIcons>();
	
	XMFLOAT2 mousePos = pMouse_->GetMousePos();

	if (IsInMousePoint(mousePos)) {

		//unitIconの移動処理
		if (pMouse_->IsPressed(Mouse::LEFT)) {
			XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
			position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
		}
		else {
			for (auto itr : pTileIcons_->GetpTIcon()) { //タイルとの当たり判定
				XMFLOAT2 leftUp = { itr->Get3DPosition().x + itr->GetGraphSizeF_2D().x / 4, itr->Get3DPosition().y };
				XMFLOAT2 graphSize = { itr->GetGraphSizeF_2D().x / 4 * 2, itr->GetGraphSizeF_2D().y };
				XMFLOAT2 graphCenter = { position.x + graphSizeF_.halfX,position.y + graphSizeF_.halfY };
				if (PointInBox({ graphCenter.x, graphCenter.y }, leftUp, graphSize)) { 
					position = { itr->Get3DPosition() };
				}
			}
		}

		//unitIconの選択処理
		if (pMouse_->IsDoubleClicked(Mouse::LEFT)) { //ダブルクリックの処理
			
			pMoveSetIcons_->GetpMoveSetIcons()[createNum_]->SetCanVisible(true);
			pMoveSelectIcons_->GetpMoveSelectIcons()[createNum_]->SetCanVisible(true);
			pMoveTypesIcons_->GetpMoveTypesIcons()[createNum_]->SetCanVisible(true);
		}
		else if (pMouse_->IsClicked(Mouse::LEFT)) { //シングルクリック
			pMoveSetIcons_->GetpMoveSetIcons()[createNum_]->SetCanVisible(false);
			pMoveSelectIcons_->GetpMoveSelectIcons()[createNum_]->SetCanVisible(false);
			pMoveTypesIcons_->GetpMoveTypesIcons()[createNum_]->SetCanVisible(false);
		}
		prevMousePos_ = mousePos;
	}
	
	if (!moveMent.empty()) {
		VECTOR pos = pTileIcons_->GetpTIcon()[moveMent.back()]->Get3DPosition();
		position = pos;
	}
}

void UnitIcon::Draw()
{
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();
	XMFLOAT2 TileSize = { pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().x,pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().y };
	if (canVisible_) {
		if (moveMent.size() > 1) {
			VECTOR pos = pTileIcons->GetpTIcon()[moveMent.front()]->Get3DPosition();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
			DrawGraph(pos.x + (TileSize.x / 2 - graphSizeF_.halfX), pos.y + (TileSize.y / 2 - graphSizeF_.halfY), hModel, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		DrawGraph(position.x + (TileSize.x / 2 - graphSizeF_.halfX), position.y + (TileSize.y / 2 - graphSizeF_.halfY), hModel, TRUE);
	}
#if 0
		DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x , position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
}
