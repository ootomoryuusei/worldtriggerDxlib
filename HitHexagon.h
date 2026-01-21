#pragma once
#include"BaseHitShape.h"
#include"Object2D.h"
class HitHexagon : public BaseHitShape { //六角形当たり判定形状クラス
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