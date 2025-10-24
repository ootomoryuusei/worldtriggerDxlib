#include "UnitIcon.h"
#include"Player1.h"

#include"TileIcons.h"
#include"MoveSetIcon.h"
#include"MoveSelectIcon.h"
#include "Mouse.h"
#include"TriggersArcIcon.h"
#include"MoveMentsLoad.h"
#include"GroupManager.h"
#include"Map.h"

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
	pArcs_ = Instantiate<TriggersArcIcon>(this);
	pLoad_ = Instantiate<MoveMentsLoad>(this);
}

void UnitIcon::Update()
{

	Mouse* pMouse_ = GetParent()->GetParent()->FindGameObject<Mouse>();
	pGroupManager_ = GetParent()->GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));
	
	MoveSetIcon* pMoveSetIcon_ = GetParent()->GetParent()->FindGameObject<MoveSetIcon>();
	MoveSelectIcon* pMoveSelectIcon_ = GetParent()->GetParent()->FindGameObject<MoveSelectIcon>();
	XMFLOAT2 mousePos = pMouse_->GetMousePos();
	pLoad_->setMoveMent(moveMent);

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
					for (auto& colmun : pTileIcons_->GetpTIcon()) {//タイルとの当たり判定
						for (auto& row : colmun) {
							XMFLOAT2 leftUp = { row->Get3DPosition().x + row->GetGraphSizeF_2D().x / 4, row->Get3DPosition().y };
							XMFLOAT2 graphSize = { row->GetGraphSizeF_2D().x / 4 * 2, row->GetGraphSizeF_2D().y };
							XMFLOAT2 graphCenter = { position.x + graphSizeF_.halfX,position.y + graphSizeF_.halfY };
							if (PointInBox({ graphCenter.x, graphCenter.y }, leftUp, graphSize)) {
								position = { row->Get3DPosition() };
							}
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
		auto& arcs = pArcs_->GetpTriggerArcIcon();
		for (auto& itr : arcs) {
			itr->Set3DPosition(position);
		}

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
			VECTOR m_front = dq_moveMent.front();
			position = pTileIcons_->GetpTIcon()[m_front.y][m_front.x]->Get3DPosition();
			firstSet = true;
			moveing = true;
		}
		if (moveing) {
			if (dq_moveMent.size() >= 2) {
				auto it = dq_moveMent.begin();
				auto s_offset = *it;
				auto t_offset = *(++it);
				
				VECTOR start = pTileIcons_->GetpTIcon()[s_offset.y][s_offset.x]->Get3DPosition();
				VECTOR target = pTileIcons_->GetpTIcon()[t_offset.y][t_offset.x]->Get3DPosition();
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
	XMFLOAT2 TileSize = { pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D().x,
		pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D().y};
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
			VECTOR m_front = moveMent.front();
			VECTOR pos = pTileIcons_->GetpTIcon()[m_front.y][m_front.x]->Get3DPosition();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
			DrawGraph(pos.x + (TileSize.x / 2 - graphSizeF_.halfX), pos.y + (TileSize.y / 2 - graphSizeF_.halfY), hModel, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		VECTOR m_back = moveMent.back();
		position = pTileIcons_->GetpTIcon()[m_back.y][m_back.x]->Get3DPosition();
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
