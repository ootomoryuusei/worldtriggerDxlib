#include "UnitIcon.h"
#include"Player1.h"

#include"TileIcons.h"
#include"MoveSetIcon.h"
#include"MoveSelectIcon.h"
#include "Mouse.h"
#include"Trigger.h"
#include"MoveMentsLoad.h"
#include"GroupManager.h"
#include"Map.h"
#include"TriggerData.h"

#include<algorithm>

using std::clamp;

UnitIcon::UnitIcon(GameObject* parent) : Object2D(parent)
{
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
	pGroupManager_ = GetParent()->GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));
	
	MoveSetIcon* pMoveSetIcon_ = GetParent()->GetParent()->FindGameObject<MoveSetIcon>();
	MoveSelectIcon* pMoveSelectIcon_ = GetParent()->GetParent()->FindGameObject<MoveSelectIcon>();
	pLoad_->setMoveMent(moveMent);


	auto& arcs = pArcs_->GetpTriggerArcIcon();
	for (auto& itr : arcs) {
		itr->SetPosition(transform_.position_);
	}

	switch (step_)
	{
	case FIRST:
	{
		if (!selecting_) return;
		//unitIconの移動処理
		for (auto& colmun : pTileIcons_->GetpTIcon()) {//タイルとの当たり判定
			for (auto& row : colmun) {
				XMFLOAT2 leftUp = { row->GetPosition().x + row->GetGraphSizeF_2D().x / 4, row->GetPosition().y };
				XMFLOAT2 graphSize = { row->GetGraphSizeF_2D().x / 4 * 2, row->GetGraphSizeF_2D().y };
				XMFLOAT2 graphCenter = { transform_.position_.x + graphSizeF_.halfX(),transform_.position_.y + graphSizeF_.halfY()};
				if (PointInBox({ graphCenter.x, graphCenter.y }, leftUp, graphSize)) {
					transform_.position_ = { row->GetPosition() };
				}
			}
		}	
		break;
	}
	case SECONDE:
	{
		for (int i = 0;i < HANDS::MAX;i++) {
			if (hands_[i] == nullptr) continue;
			const auto& data = arcs[i]->GetpData()->GetTriggerData();
			hands_[i]->GetTriggerData()->SetTriggerData(data);
		}
			/*	if (!moveMent.empty()) {
		        VECTOR pos = pTileIcons_->GetpTIcon()[moveMent.back()]->Get3DPosition();
				position = pos;
			}*/
		break;
	}
	case THIRD:
	{		
		if (!firstSet) {
			for (auto& itr : moveMent) {
				dq_moveMent.push_back(itr);
			}
			auto m_front = dq_moveMent.front();
			transform_.position_ = pTileIcons_->GetpTIcon()[m_front.movement.y][m_front.movement.x]->GetPosition();
			firstSet = true;
			moveing = true;
		}
		if (moveing) {
			if (dq_moveMent.size() >= 2) {
				auto it = dq_moveMent.begin();
				auto s_offset = *it;
				auto t_offset = *(++it);
				
				XMFLOAT3 start = pTileIcons_->GetpTIcon()[s_offset.movement.y][s_offset.movement.x]->GetPosition();
				XMFLOAT3 target = pTileIcons_->GetpTIcon()[t_offset.movement.y][t_offset.movement.x]->GetPosition();
				float percent = elapsedTime / totalTime;
				percent = clamp(percent, 0.0f, 1.0f);
				transform_.position_ = Lerp3D(start, target, percent);
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
	Object2D::Update();
}

void UnitIcon::Draw()
{
	XMFLOAT2 TileSize = { pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D().x,
		pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D().y};
	switch (step_)
	{
	case FIRST:
	{
		DrawGraph(transform_.position_.x + (TileSize.x / 2 - graphSizeF_.halfX()), transform_.position_.y + (TileSize.y / 2 - graphSizeF_.halfY()), hModel_, TRUE);
		break;
	}
	case SECONDE:
	{
		if (moveMent.size() >= 2) {
			auto m_front = moveMent.front();
			XMFLOAT3 pos = pTileIcons_->GetpTIcon()[m_front.movement.y][m_front.movement.x]->GetPosition();
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
			DrawGraph(pos.x + (TileSize.x / 2 - graphSizeF_.halfX()), pos.y + (TileSize.y / 2 - graphSizeF_.halfY()), hModel_, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		auto m_back = moveMent.back();
		transform_.position_ = pTileIcons_->GetpTIcon()[m_back.movement.y][m_back.movement.x]->GetPosition();
		DrawGraph(transform_.position_.x + (TileSize.x / 2 - graphSizeF_.halfX()), transform_.position_.y + (TileSize.y / 2 - graphSizeF_.halfY()), hModel_, TRUE);
		break;
	}
	case THIRD:
	{
		DrawGraph(transform_.position_.x + (TileSize.x / 2 - graphSizeF_.halfX()), transform_.position_.y + (TileSize.y / 2 - graphSizeF_.halfY()), hModel_, TRUE);
		break;
	}	
	default:
		break;
	}
#if 0
	DrawBoxAA(position.x, position.y, position.x + graphSizeF_.x , position.y + graphSizeF_.y, GetColor(255, 0, 0), FALSE);
#endif
}

void UnitIcon::DeviceEvent(const ClickEvent& event)
{
	switch (event.button)
	{
	case LEFT:
		//行動選択、行動一覧を生成
		set = false;
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}

void UnitIcon::DeviceEvent(const DoubleClickEvent& event)
{
	switch (event.button)
	{
	case LEFT:
		//行動選択、行動一覧、ユニットの範囲外だった場合消去
		set = true;
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}

void UnitIcon::DeviceEvent(const DragEvent& event)
{
	switch (event.button)
	{
	case LEFT:
		if (!selecting_) return;
		XMFLOAT2 current_pos = event.current;
		XMFLOAT2 prev_pos = event.start;
		XMFLOAT2 mouseVariation = { current_pos.x - prev_pos.x,current_pos.y - prev_pos.y };
		transform_.position_ = { transform_.position_.x + mouseVariation.x, transform_.position_.y + mouseVariation.y, 0.0f };
		prev_pos = current_pos;
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}
