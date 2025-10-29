#include "TriggerArcIcon.h"
#include"Mouse.h"
#include"TileIcons.h"
#include"UnitIcons.h"
#include"TriggerData.h"
#include"GroupManager.h"
#include <algorithm>

using std::clamp;

TriggerArcIcon::TriggerArcIcon(GameObject* parent) : Icon(parent)
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
	percent = 5.0f;
	startPercent = -5.0f;
	VECTOR prevVec = { 0,0,0 };
	pData_ = Instantiate<TriggerData>(this);
	TRIGGER trigger;
	trigger.arc.percent = 5.0f;
	trigger.arc.rangeSize = 1.5f;
	trigger.arc.startPercent = -5.0f;
	pData_->SetTriggerData(trigger);
	pGroupManager_ = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<GroupManager>();
	pTileIcons_ = dynamic_cast<TileIcons*>(pGroupManager_->GetGroup("TileIconGroup"));
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
			calculateArc();
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

					VECTOR start = {startIndex.x,startIndex.y,0};
					VECTOR target = {targetIndex.x,targetIndex.y,0};
					float Percent = elapsedTime / totalTime;
					Percent = clamp(Percent, 0.0f, 1.0f);
					startPercent = Lerp3D(start, target, Percent).x;
					percent = Lerp3D(start, target, Percent).y;
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
}

void TriggerArcIcon::Draw()
{
	const auto& uniticons = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
	SIZE_F_2D tileSize = pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D();
	XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX - tileSize.halfX),
								position.y + (graphSizeF_.halfY - tileSize.halfY) };

	float size = pData_->GetTriggerData().arc.rangeSize;
	DrawCircleGaugeF(DrawCenterPos.x, DrawCenterPos.y, percent, hModel, startPercent,size);

	//if (hand_ == RIGHT) {
	//	/*DrawRotaStringF()*/
	//	DrawString(boxCorners[0].x, boxCorners[0].y, "Main", GetColor(255, 255, 255), 1.5);
	//}
	//else if(hand_ == LEFT){
	//	DrawString(boxCorners[0].x, boxCorners[0].y, "Sub", GetColor(255, 255, 255), 1.5);
	//}
#if 0
	// 四角形描画
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		DrawLineAA(boxCorners[i].x, boxCorners[i].y,
			boxCorners[j].x, boxCorners[j].y,
			GetColor(255, 0, 0), FALSE);
	}
	for (int i = 0; i < 4; ++i) {
		DrawCircle(boxCorners[i].x, boxCorners[i].y, 2,GetColor(0,255,0)); // 四隅のマーク
	}
#endif
}

void TriggerArcIcon::calculateArc()
{
	const auto& uniticons = GetParent()->GetParent()->GetParent()->GetParent()->FindGameObject<UnitIcons>();
	const auto& mouse = uniticons->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = mouse->GetMousePos();	
	SIZE_F_2D tileSize = pTileIcons_->GetpTIcon()[0][0]->GetGraphSizeF_2D();
	XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX - tileSize.halfX),
		position.y + (graphSizeF_.halfY - tileSize.halfY) };


	// 扇形の角度と中心角の向きを取得
	float startAngleDeg = startPercent * 3.6f;
	float endAngleDeg = percent * 3.6f;
	float centerAngleDeg = (startAngleDeg + endAngleDeg) / 2.0f;
	float angleRad = XMConvertToRadians(centerAngleDeg);

	// 四角形サイズ（幅は角度に応じて、高さは固定）
	float angleSpanDeg = endAngleDeg - startAngleDeg;
	float size = pData_->GetTriggerData().arc.rangeSize;
	float width = graphSizeF_.halfX * size * sqrtf(2 * (1 - cos(XMConvertToRadians(angleSpanDeg))));
	float height = graphSizeF_.halfY * size;

	// 四角形のローカル座標（原点は底辺中央）
	XMFLOAT2 localCorners[4] = {
		{-width / 2, -height}, // 左上（←ここからスタート）
		{ width / 2, -height}, // 右上
		{ width / 2, 0},       // 右下
		{-width / 2, 0}        // 左下
	};

	// 回転中心（DrawCircleGauge と同じ）
	center = DrawCenterPos;

	// ローカル→ワールド座標へ変換（回転あり）
	for (int i = 0; i < 4; i++) {
		float x = localCorners[i].x;
		float y = localCorners[i].y;
		boxCorners[i].x = center.x + x * cos(angleRad) - y * sin(angleRad);
		boxCorners[i].y = center.y + x * sin(angleRad) + y * cos(angleRad);
	}

	VECTOR nowVec, centerVec;
	if (selecting_) { //選択中
		if (mouse->IsPressed(Mouse::LEFT)) {
			nowVec = { mousePos.x, mousePos.y, 0 };
			centerVec = { center.x, center.y, 0 };

			VECTOR startVec = nowVec - centerVec;
			VECTOR nextVec = prevVec - centerVec;

			VECTOR cross = VCross(nextVec, startVec);
			if (cross.z < 0) { // 時計回り
				startPercent -= 0.5;
				percent -= 0.5;
			}
			else if (cross.z > 0) { // 反時計回り
				startPercent += 0.5;
				percent += 0.5;
			}

			// 次フレームのために保存
			prevVec = nowVec;
		}
	}
}
