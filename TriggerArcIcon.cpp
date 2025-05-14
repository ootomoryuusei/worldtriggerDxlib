#include "TriggerArcIcon.h"
#include"Mouse.h"
#include"TileIcons.h"
#include"UnitIcons.h"

TriggerArcIcon::TriggerArcIcon(GameObject* parent) : Icon(parent)
{
	step_ = SECONDE;
}

TriggerArcIcon::~TriggerArcIcon()
{
}

void TriggerArcIcon::Initialize()
{
	percent = 40.0f;
	startPercent = 20.0f;
	VECTOR prevVec = { 0,0,0 };
}

void TriggerArcIcon::Update()
{
	if (canVisible_) {
		switch (step_)
		{
		case Icon::FIRST:
		{
			canVisible_ = false;
		}
			break;
		case Icon::SECONDE:
		{
			canVisible_ = true;
			calculateArc();
			break;
		}
		case Icon::THIRD:
			break;
		default:
			break;
		}
	}
}

void TriggerArcIcon::Draw()
{
	TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
	SIZE_F_2D tileSize = pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D();
	XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX - tileSize.halfX),
								position.y + (graphSizeF_.halfY - tileSize.halfY) };

	if (canVisible_) {
		DrawCircleGaugeF(DrawCenterPos.x, DrawCenterPos.y, percent, hModel, startPercent);

		if (createNum_ == 0) {
			/*DrawRotaStringF()*/
			DrawString(boxCorners[0].x, boxCorners[0].y, "Main", GetColor(255, 255, 255), 1.5);
		}
		else {
			DrawString(boxCorners[0].x, boxCorners[0].y, "Sub", GetColor(255, 255, 255), 1.5);
		}
	}
#if 0
	// 四角形描画
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		DrawLineAA(boxCorners[i].x, boxCorners[i].y,
			boxCorners[j].x, boxCorners[j].y,
			GetColor(255, 0, 0), FALSE);
	}
	Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();
	for (int i = 0; i < 4; ++i) {
		DrawCircle(boxCorners[i].x, boxCorners[i].y, 5,GetColor(0,255,0)); // 四隅のマーク
	}
	DrawCircle(mousePos.x, mousePos.y, 5, GetColor(0,0,255)); // マウス位置
#endif
}

void TriggerArcIcon::calculateArc()
{
	Mouse* pMouse = GetParent()->GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();
	TileIcons* pTileIcons = GetParent()->GetParent()->GetParent()->FindGameObject<TileIcons>();
	SIZE_F_2D tileSize = pTileIcons->GetpTIcon()[0]->GetGraphSizeF_2D();
	XMFLOAT2 DrawCenterPos = { position.x + (graphSizeF_.halfX - tileSize.halfX),
		position.y + (graphSizeF_.halfY - tileSize.halfY) };


	// 扇形の角度と中心角の向きを取得
	float startAngleDeg = startPercent * 3.6f;
	float endAngleDeg = percent * 3.6f;
	float centerAngleDeg = (startAngleDeg + endAngleDeg) / 2.0f;
	float angleRad = XMConvertToRadians(centerAngleDeg);

	// 四角形サイズ（幅は角度に応じて、高さは固定）
	float angleSpanDeg = endAngleDeg - startAngleDeg;
	float width = graphSizeF_.halfX * sqrtf(2 * (1 - cos(XMConvertToRadians(angleSpanDeg))));
	float height = graphSizeF_.halfY;

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
		if (pMouse->IsPressed(Mouse::LEFT)) {
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
