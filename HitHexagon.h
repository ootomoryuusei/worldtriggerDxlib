#pragma once
#include"BaseHitShape.h"
#include"Object2D.h"
class HitHexagon : public BaseHitShape { //六角形当たり判定形状クラス
public:
	vector<XMFLOAT2> corners_;

	void Rebulid(const Transform& tranform) override {
	}
	bool IsHit(XMFLOAT2& point, Object2D& element) override {
		OBJ_SIZE_F hitSize = element.GetHitSizeF();
		XMFLOAT3 position = element.GetPosition();

		XMFLOAT2 center = { position.x + hitSize.halfX(),position.y + hitSize.halfY() };

		float startAngle = -XM_PI / 2.0f;
		float radius = element.GetScale().x * 0.5f;

		for(int i = 0; i<6;i++) {
			float angle = startAngle + element.GetRotate().x + i * (2.0f * XM_PI / 6.0f);
			corners_.push_back({ center.x + cosf(angle) * radius,
								 center.y + sinf(angle) * radius});
		}
		for(const auto& corner : corners_) {
			return element.PointInPolygon(point, corners_);
		}
		return false;
	}
};