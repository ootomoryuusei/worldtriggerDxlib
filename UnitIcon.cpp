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
#include"HitSquare.h"
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
	Object2D::Initialize(); //raycaster2Dへ登録
	hitShape_ = new HitSquare(); // 当たり判定形状を四角形に設定
	maxMoveMent = 10;
	pArcs_ = Instantiate<TriggersArcIcon>(this);
	pLoad_ = Instantiate<MoveMentsLoad>(this);
}

void UnitIcon::Update()
{
	pGroupManager_ = GetParent()->GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));
	SetScale(pTileIcons_->GetScale()); //タイルと同じscaleに
	
	MoveSetIcon* pMoveSetIcon_ = GetParent()->GetParent()->FindGameObject<MoveSetIcon>();
	MoveSelectIcon* pMoveSelectIcon_ = GetParent()->GetParent()->FindGameObject<MoveSelectIcon>();
	pLoad_->setMoveMent(moveMent);
	


	auto& arcs = pArcs_->GetpTriggerArcIcon();
	for (auto& arc : arcs) {
		arc->SetPosition(transform_.position_);
	}

	switch (step_)
	{
	case FIRST:
	{
		if (!selecting_) return;
		//unitIconの移動処理
		for (auto& colmun : pTileIcons_->GetpTIcon()) {//タイルとの当たり判定
			for (auto& row : colmun) {
				XMFLOAT2 leftUp = { row->GetPosition().x + row->GetBaseSizeF().x / 4, row->GetPosition().y };
				XMFLOAT2 graphSize = { row->GetBaseSizeF().x / 4 * 2, row->GetBaseSizeF().y };
				XMFLOAT2 graphCenter = { transform_.position_.x + GetBaseSizeF().halfX(),transform_.position_.y + GetBaseSizeF().halfY()};
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
	OBJ_SIZE_F tileSize = pTileIcons_->GetBaseSizeF();
	/*if (moveMent.size() >= 2) {
		auto m_front = moveMent.front();
		transform_.position_ = pTileIcons_->GetpTIcon()[m_front.movement.y][m_front.movement.x]->GetPosition();
	}*/
	auto m_back = moveMent.back();
	transform_.position_ = pTileIcons_->GetpTIcon()[m_back.movement.y][m_back.movement.x]->GetPosition();
	/*transform_.position_ +=  (tileSize / 2 - graphSizeF_.half());*/
	transform_.position_ += tileSize.half() * pTileIcons_->GetScale() - hitSize_.half();
	Object2D::Update();
}

void UnitIcon::Draw()
{
	switch (step_)
	{
	case FIRST:
	{
		Object2D::Draw();
		break;
	}
	case SECONDE:
	{
		if (moveMent.size() >= 2) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 / 2);
			Object2D::Draw();
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		Object2D::Draw();
		break;
	}
	case THIRD:
	{
		Object2D::Draw();
		break;
	}	
	default:
		break;
	}
#if 0
	DrawBoxAA(position_.x, position_.y, 
		position_.x + baseSize_.x * transform_.scale_.x, position_.y + baseSize_.y * transform_.scale_.x, GetColor(255, 0, 0), FALSE);
#endif
}

void UnitIcon::DeviceEvent(const ClickEvent& event)
{
	switch (event.button)
	{
	case LEFT: 
	{
		//行動選択、行動一覧を生成
		set = false;
	}
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
	{
		//行動選択、行動一覧、ユニットの範囲外だった場合消去
		set = true;
	}
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
	XMFLOAT2 offset = event.delta;
	switch (event.button)
	{
	case LEFT:
		if (!selecting_) return;
		SetPosition(transform_.position_.x + offset.x, transform_.position_.y + offset.y, transform_.position_.z);
		break;
	case RIGHT:
		break;
	case MIDDLE:
		break;
	default:
		break;
	}
}
