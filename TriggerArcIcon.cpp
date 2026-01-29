#include "TriggerArcIcon.h"
#include"Mouse.h"
#include"TileIcons.h"
#include"UnitIcons.h"
#include"TriggerData.h"
#include"GroupManager.h"
#include <algorithm>

using std::clamp;

TriggerArcIcon::TriggerArcIcon(GameObject* parent) : ArcIcon(parent)
{
	step_ = SECONDE;

	firstSet = false;
	moveing = false;

	totalTime = 10.0f;

	elapsedTime = 0.0f;
}

TriggerArcIcon::~TriggerArcIcon()
{
}

void TriggerArcIcon::Initialize()
{
	ArcIcon::Initialize(); // 当たり判定形状を円弧専用四角形に設定
	VECTOR prevVec = { 0,0,0 };
	pData_ = Instantiate<TriggerData>(this);
	TRIGGER trigger;
	trigger.arc.percent = 5.0f;
	trigger.arc.rangeSize = 1.5f;
	trigger.arc.startPercent = -5.0f;
	arcData_ = trigger.arc;
	pData_->SetTriggerData(trigger);
	pGroupManager_ = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));

	SetScale(trigger.arc.rangeSize, trigger.arc.rangeSize, 0);
}

void TriggerArcIcon::Update()
{
		switch (step_)
		{
		case FIRST:
		{
		}
			break;
		case SECONDE:
		{
			break;
		}
		case THIRD:
			
			if (!firstSet) {
				for (auto& itr : angle) {
					dq_angle.push_back(itr);
				}
				firstSet = true;
				moveing = true;
			}
			if (moveing) {
				if (dq_angle.size() >= 2) {
					auto it = dq_angle.begin();
					auto startIndex = *it;
					auto targetIndex = *(++it);

					XMFLOAT3 start = {startIndex.x,startIndex.y,0};
					XMFLOAT3 target = {targetIndex.x,targetIndex.y,0};
					float Percent = elapsedTime / totalTime;
					Percent = clamp(Percent, 0.0f, 1.0f);
					arcData_.startPercent = Lerp3D(start, target, Percent).x;
					arcData_.percent = Lerp3D(start, target, Percent).y;
					if (Percent >= 1.0f) {
						// 移動完了 → 次の区間へ
						elapsedTime = 0.0f;
						dq_angle.pop_front();
					}
				}

				if (dq_angle.size() < 2) {
					moveing = false;
				}
				elapsedTime += Time::DeltaTime();
			}
			break;
		default:
			break;
		}
		OBJ_SIZE_F tileSize = pTileIcons_->GetpTIcon()[0][0]->GetBaseSizeF();
		transform_.position_ += tileSize.half();
		ArcIcon::Update();
		
}

void TriggerArcIcon::Draw()
{
	const auto& uniticons = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
	

	ArcIcon::Draw();
	/*DrawCircleGaugeF(DrawCenterPos.x, DrawCenterPos.y, percent, hModel_, startPercent,scale_.x);*/

	//if (hand_ == RIGHT) {
	//	/*DrawRotaStringF()*/
	//	DrawString(boxCorners[0].x, boxCorners[0].y, "Main", GetColor(255, 255, 255), 1.5);
	//}
	//else if(hand_ == LEFT){
	//	DrawString(boxCorners[0].x, boxCorners[0].y, "Sub", GetColor(255, 255, 255), 1.5);
	//}
}

void TriggerArcIcon::DeviceEvent(const DragEvent& event)
{
	switch (event.button)
	{
	case LEFT:
	{
		OBJ_SIZE_F tileSize = pTileIcons_->GetpTIcon()[0][0]->GetHitSizeF();
		XMFLOAT3 DrawCenterPos = transform_.position_ + tileSize.half();
		
		//回転中心（DrawCircleGauge と同じ）
		center = { DrawCenterPos.x,DrawCenterPos.y };

		VECTOR nowVec, prevVec;
		nowVec = { event.current.x - center.x, event.current.y - center.y, 0 };
		prevVec = { nowVec.x - event.delta.x, nowVec.y - event.delta.y, 0 };

		float lenNow = sqrtf(nowVec.x * nowVec.x + nowVec.y * nowVec.y);
		float lenPrev = sqrtf(prevVec.x * prevVec.x + prevVec.y * prevVec.y);

		if (lenNow < 10.0f || lenPrev < 10.0f)
			return;

		float newAngle = atan2f(nowVec.y, nowVec.x);
		float prevAngle = atan2f(prevVec.y, prevVec.x);

		float deltaAngle = remainder(newAngle - prevAngle, DX_TWO_PI_F); //-パイ～パイの範囲に収める(ラップ)

		float deltaPercent = deltaAngle * (100.0f / DX_TWO_PI_F); //ラジアンをパーセントに変換 

		arcData_.startPercent += deltaPercent;
		arcData_.percent = arcData_.startPercent + 10.0f;
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

void TriggerArcIcon::calculateArc()
{
	
}
