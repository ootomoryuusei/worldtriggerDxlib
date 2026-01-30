#pragma once
#include"BaseHitShape.h"
#include"Object2D.h"
class HitHexagon : public BaseHitShape { //六角形当たり判定形状クラス
public:

	void Rebuild(Object2D& element) override {
		corners_.clear();
		cornersNum_ = 6;
		OBJ_SIZE_F hitSize = element.GetHitSizeF();
		XMFLOAT3 position = element.GetPosition();

		XMFLOAT2 center = { position.x + hitSize.halfX(),position.y + hitSize.halfY() };

		float startAngle = -XM_PI / 2.0f;
		float radius = element.GetScale().x * 0.5f;

		for (int i = 0; i < cornersNum_;i++) {
			float angle = startAngle + element.GetRotate().x + i * (2.0f * XM_PI / 6.0f);
			corners_.push_back({ center.x + cosf(angle) * radius,
								 center.y + sinf(angle) * radius });
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