#pragma once
#include"Object2D.h"
#include"ArcIcon.h"
#include"TriggerData.h"
class HitSquareArc : public BaseHitShape { //円弧専用四角形当たり判定形状クラス
public:
	vector<XMFLOAT2> corners_;

	void Rebulid(const Transform& tranform) override {
	}
	bool IsHit(const XMFLOAT2& point, Object2D& element) override {
		corners_.clear();
		
		const size_t cornersNum = 4;
		const auto& ui = dynamic_cast<ArcIcon*> (&element);
		OBJ_SIZE_F hitSize = element.GetHitSizeF();
		XMFLOAT3 position = element.GetPosition();
		XMFLOAT3 scale = element.GetScale();
		ARC_DATA arc = ui->GetArcData();

		XMFLOAT2 center = { position.x + hitSize.halfX(),position.y + hitSize.halfY() };

		float startAngle = -XM_PI / 2.0f;
		float radius = element.GetScale().x * 0.5f;

		for (int i = 0; i < cornersNum;i++) {
			float angle = startAngle + element.GetRotate().x + i * (2.0f * XM_PI / 6.0f);
			corners_.push_back({ center.x + cosf(angle) * radius,
								 center.y + sinf(angle) * radius });
		}

		// 扇形の角度と中心角の向きを取得
		float startAngleDeg = arc.startPercent * 3.6f;
		float endAngleDeg = arc.percent * 3.6f;
		float centerAngleDeg = (startAngleDeg + endAngleDeg) / 2.0f;
		float angleRad = XMConvertToRadians(centerAngleDeg);

		// 四角形サイズ（幅は角度に応じて、高さは固定）
		float angleSpanDeg = endAngleDeg - startAngleDeg;
		float width =  sqrtf(2 * (1 - cos(XMConvertToRadians(angleSpanDeg))));
		float height = hitSize.halfY();

		/*hitSize_.set(width, height, 0);*/
		// 四角形のローカル座標（原点は底辺中央）
		XMFLOAT2 localCorners[4] = {
			{-width / 2, -height}, // 左上（←ここからスタート）
			{ width / 2, -height}, // 右上
			{ width / 2, 0},       // 右下
			{-width / 2, 0}        // 左下
		};

		// 回転中心（DrawCircleGauge と同じ）
		center = { position.x,position.y };

		// ローカル→ワールド座標へ変換（回転あり）
		for (int i = 0; i < cornersNum; i++) {
			float x = localCorners[i].x;
			float y = localCorners[i].y;
			corners_[i].x = center.x + x * cos(angleRad) - y * sin(angleRad);
			corners_[i].y = center.y + x * sin(angleRad) + y * cos(angleRad);
		}
		return element.PointInPolygon(point, corners_);
	}

	void DrawJudgmentRange(Object2D& element) override {
		const size_t cornersNum = 4;
		for (int i = 0; i < cornersNum; i++) {
			int j = (i + 1) % cornersNum;
			DrawLineAA(corners_[i].x, corners_[i].y,
				corners_[j].x, corners_[j].y,
				GetColor(255, 0, 0), FALSE);
		}
		for (int i = 0; i < cornersNum; ++i) {
			DrawCircle(corners_[i].x, corners_[i].y, 2, GetColor(0, 255, 0)); // 六角形の頂点のマーク
		}
	}

};