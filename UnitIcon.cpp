#include "UnitIcon.h"
#include"Player1.h"

#include"TileIcons.h"
#include"MoveSetIcon.h"
#include"MoveSelectIcon.h"
#include "Mouse.h"
#include"TriggersArcIcon.h"

#include<algorithm>

using std::clamp;

UnitIcon::UnitIcon(GameObject* parent) : Icon(parent)
{
	canVisible_ = true;

	createNum_ = -1;

	step_ = SECONDE;

	firstSet = false;
	moveing = false;

	totalTime = 10.0f;

	elapsedTime = 0.0f;

	set = false;
}

UnitIcon::~UnitIcon()
{
}

void UnitIcon::Initialize()
{
	maxMoveMent = 10;
	/*pArcs_ = Instantiate<TriggersArcIcon>(this);*/
}

void UnitIcon::Update()
{

	Mouse* pMouse_ = GetParent()->GetParent()->FindGameObject<Mouse>();
	TileIcons* pTileIcons_ = GetParent()->GetParent()->FindGameObject<TileIcons>();
	
	MoveSetIcon* pMoveSetIcon_ = GetParent()->GetParent()->FindGameObject<MoveSetIcon>();
	MoveSelectIcon* pMoveSelectIcon_ = GetParent()->GetParent()->FindGameObject<MoveSelectIcon>();
	XMFLOAT2 mousePos = pMouse_->GetMousePos();

	switch (step_)
	{
	case FIRST:
	{
		if (IsInMousePoint(mousePos)) {
			if (selecting_) {
				//unitIconの移動処理
				if (pMouse_->IsPressed(Mouse::LEFT)) {
					XMFLOAT2 mouseVariation = { mousePos.x - prevMousePos_.x,mousePos.y - prevMousePos_.y };
					position = { position.x + mouseVariation.x, position.y + mouseVariation.y, 0.0f };
				}else {
					for (auto itr : pTileIcons_->GetpTIcon()) { //タイルとの当たり判定
						XMFLOAT2 leftUp = { itr->Get3DPosition().x + itr->GetGraphSizeF_2D().x / 4, itr->Get3DPosition().y };
						XMFLOAT2 graphSize = { itr->GetGraphSizeF_2D().x / 4 * 2, itr->GetGraphSizeF_2D().y };
						XMFLOAT2 graphCenter = { position.x + graphSizeF_.halfX,position.y + graphSizeF_.halfY };
						if (PointInBox({ graphCenter.x, graphCenter.y }, leftUp, graphSize)) {
							position = { itr->Get3DPosition() };
						}
					}
				}
			}
		}
		prevMousePos_ = mousePos;
		break;
	}
	case SECONDE:
	{
		/*auto& arcs = pArcs_->GetpTriggerArcIcon();
		for (auto& itr : arcs) {
			itr->SetAngle()
		}*/
		if (IsInMousePoint(mousePos)) {
			//unitIconの選択処理
			if (pMouse_->IsDoubleClicked(Mouse::LEFT)) { //ダブルクリック処理
				//行動選択、行動一覧を生成
				set = true;
			}else if (pMouse_->IsClicked(Mouse::LEFT)) { //シングルクリック処理
				//行動選択、行動一覧、ユニットの範囲外だった場合消去
				set = false;
			}
			/*	if (!moveMent.empty()) {
		        VECTOR pos = pTileIcons_->GetpTIcon()[moveMent.back()]->Get3DPosition();
				position = pos;
			}*/
		}
		break;
	}
	case THIRD:
	{		
		if (!firstSet) {
			for (auto& itr : moveMent) {
				dq_moveMent.push_back(itr);
			}
			position = pTileIcons_->GetpTIcon()[dq_moveMent.front()]->Get3DPosition();
			firstSet = true;
			moveing = true;
		}
		if (moveing) {
			if (dq_moveMent.size() >= 2) {
				auto it = dq_moveMent.begin();
				auto startIndex = *it;
				auto targetIndex = *(++it);
				
				VECTOR start = pTileIcons_->GetpTIcon()[startIndex]->Get3DPosition();
				VECTOR target = pTileIcons_->GetpTIcon()[targetIndex]->Get3DPosition();
				float percent = elapsedTime / totalTime;
				percent = clamp(percent, 0.0f, 1.0f);
				position = Lerp3D(start, target, percent);
				if (percent >= 1.0f) {
					// 移動完了 → 次の区間へ
					elapsedTime = 0.0f;
					dq_moveMent.pop_front();
				}
			}
			if (dq_moveMent.size() < 2) {
				moveing = false;
			}
			elapsedTime += Time::DeltaTime();
		}
		break;
	}
	default:
		break;
	}
}

void UnitIcon::Draw()
{
	TileIcons* pTileIcons = GetParent()->GetParent()->FindGameObject<TileIcons>();
	XMFLOAT2 TileSize = { pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().x,pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D().y };
	switch (step_)
	{
	case FIRST:
	{
		DrawGraph(position.x + (TileSize.x / 2 - graphSizeF_.halfX), position.y + (TileSize.y / 2 - graphSizeF_.halfY), hModel, TRUE);
		break;
	}
	case SECONDE:
	{
		if (moveMent.size() >= 2) {
			VECTOR pos = pTileIcons->GetpTIcon()[moveMent.front()]->Get3DPosition();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
			DrawGraph(pos.x + (TileSize.x / 2 - graphSizeF_.halfX), pos.y + (TileSize.y / 2 - graphSizeF_.halfY), hModel, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		position = pTileIcons->GetpTIcon()[moveMent.back()]->Get3DPosition();
		DrawGraph(position.x + (TileSize.x / 2 - graphSizeF_.halfX), position.y + (TileSize.y / 2 - graphSizeF_.halfY), hModel, TRUE);
		break;
	}
	case THIRD:
	{
		DrawGraph(position.x + (TileSize.x / 2 - graphSizeF_.halfX), position.y + (TileSize.y / 2 - graphSizeF_.halfY), hModel, TRUE);
		break;
	}	
	default:
		break;
	}
#if 0
	DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x , position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
}
