#pragma once
#include"Object2D.h"
#include"TriggerData.h"
class HitSquareArc : public BaseHitShape { //円弧専用四角形当たり判定形状クラス
public:
	vector<XMFLOAT2> corners_;

	void Rebulid(const Transform& tranform) override {
	}
	bool IsHit(const XMFLOAT2& point, Object2D& element) override {
		corners_.clear();

		OBJ_SIZE_F hitSize = element.GetHitSizeF();
		XMFLOAT3 position = element.GetPosition();

		XMFLOAT2 center = { position.x + hitSize.halfX(),position.y + hitSize.halfY() };

		float startAngle = -XM_PI / 2.0f;
		float radius = element.GetScale().x * 0.5f;

		for (int i = 0; i < 6;i++) {
			float angle = startAngle + element.GetRotate().x + i * (2.0f * XM_PI / 6.0f);
			corners_.push_back({ center.x + cosf(angle) * radius,
								 center.y + sinf(angle) * radius });
		}

		OBJ_SIZE_F tileSize = pTileIcons_->GetpTIcon()[0][0]->GetHitSizeF();
		XMFLOAT3 DrawCenterPos = position + tileSize.half();
		OBJ_SIZE_F base_size = element.GetBaseSizeF();

		// 扇形の角度と中心角の向きを取得
		float startAngleDeg = startPercent * 3.6f;
		float endAngleDeg = percent * 3.6f;
		float centerAngleDeg = (startAngleDeg + endAngleDeg) / 2.0f;
		float angleRad = XMConvertToRadians(centerAngleDeg);

		// 四角形サイズ（幅は角度に応じて、高さは固定）
		float angleSpanDeg = endAngleDeg - startAngleDeg;
		float width = baseSize_.halfX() * transform_.scale_.x * sqrtf(2 * (1 - cos(XMConvertToRadians(angleSpanDeg))));
		float height = baseSize_.halfY() * transform_.scale_.y;

		hitSize_.set(width, height, 0);
		// 四角形のローカル座標（原点は底辺中央）
		XMFLOAT2 localCorners[4] = {
			{-width / 2, -height}, // 左上（←ここからスタート）
			{ width / 2, -height}, // 右上
			{ width / 2, 0},       // 右下
			{-width / 2, 0}        // 左下
		};

		// 回転中心（DrawCircleGauge と同じ）
		center = { DrawCenterPos.x,DrawCenterPos.y };

		// ローカル→ワールド座標へ変換（回転あり）
		for (int i = 0; i < 4; i++) {
			float x = localCorners[i].x;
			float y = localCorners[i].y;
			corners_[i].x = center.x + x * cos(angleRad) - y * sin(angleRad);
			corners_[i].y = center.y + x * sin(angleRad) + y * cos(angleRad);
		}
		return element.PointInPolygon(point, corners_);
	}

	void DrawJudgmentRange(Object2D& element) override {
		const auto& corners = corners_;
		for (int i = 0; i < 6; i++) {
			int j = (i + 1) % 6;
			DrawLineAA(corners[i].x, corners[i].y,
				corners[j].x, corners[j].y,
				GetColor(255, 0, 0), FALSE);
		}
		for (int i = 0; i < 6; ++i) {
			DrawCircle(corners[i].x, corners[i].y, 2, GetColor(0, 255, 0)); // 六角形の頂点のマーク
		}
	}
};