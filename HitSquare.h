#pragma once
#include"Object2D.h"
class HitSquare : public BaseHitShape { //四角形当たり判定形状クラス
public:
	void Rebulid(const Transform& tranform) override {
	}
	bool IsHit(XMFLOAT2& point, Object2D& element) override {
		return element.IsInMousePoint(point);
	}
};