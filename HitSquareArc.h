#pragma once
#include"Object2D.h"
#include"ArcIcon.h"
#include"TriggerData.h"
class HitSquareArc : public BaseHitShape { //円弧専用四角形当たり判定形状クラス
public:
	void Rebuild(Object2D& element) override {
		corners_.clear();

		cornersNum_ = 4;
		const auto& ui = dynamic_cast<ArcIcon*> (&element);
		ARC_DATA arc = ui->GetArcData();
		OBJ_SIZE_F hitSize = element.GetHitSizeF();

		// 扇形の角度と中心角の向きを取得
		float startAngleDeg = arc.startPercent * 3.6f;
		float endAngleDeg = arc.percent * 3.6f;
		float centerAngleDeg = (startAngleDeg + endAngleDeg) / 2.0f;
		float angleRad = XMConvertToRadians(centerAngleDeg);

		// 四角形サイズ（幅は角度に応じて、高さは固定）
		float angleSpanDeg = endAngleDeg - startAngleDeg;
		float width = hitSize.halfX() * sqrtf(2 * (1 - cos(XMConvertToRadians(angleSpanDeg))));
		float height = hitSize.halfY();

		/*hitSize_.set(width, height, 0);*/
		// 四角形のローカル座標（原点は底辺中央）
		XMFLOAT2 localCorners[4] = {
			{-width / 2, -height}, // 左上（←ここからスタート）
			{ width / 2, -height}, // 右上
			{ width / 2, 0},       // 右下
			{-width / 2, 0}        // 左下
		};

		XMFLOAT2 center = { element.GetPosition().x,element.GetPosition().y };

		// ローカル→ワールド座標へ変換（回転あり）
		for (int i = 0; i < cornersNum_; i++) {
			float x = localCorners[i].x;
			float y = localCorners[i].y;
			float cornerX = center.x + x * cos(angleRad) - y * sin(angleRad);
			float cornerY = center.y + x * sin(angleRad) + y * cos(angleRad);
			corners_.push_back({ cornerX,cornerY });
		}
	}

	bool IsHit(const XMFLOAT2& point, Object2D& element) override {
		Rebuild(element);
		return element.PointInPolygon(point, corners_);
	}

	void DrawJudgmentRange(Object2D& element) override {
		for (int i = 0; i < cornersNum_; i++) {
			int j = (i + 1) % cornersNum_;
			DrawLineAA(corners_[i].x, corners_[i].y,
				corners_[j].x, corners_[j].y,
				GetColor(255, 0, 0), FALSE);
		}
		for (int i = 0; i < cornersNum_; ++i) {
			DrawCircle(corners_[i].x, corners_[i].y, 2, GetColor(0, 255, 0)); // 六角形の頂点のマーク
		}
	}
};