#pragma once
#include"BaseHitShape.h"
#include"Object2D.h"
class HitHexagon : public BaseHitShape { //六角形当たり判定形状クラス
public:
	vector<XMFLOAT2> corners_;
	bool IsHit(XMFLOAT2& point, Object2D& element) override {
		XMFLOAT3 size = element.GetHitSizeF().size();
		XMFLOAT3 position = element.GetPosition();
		corners_[0] = { position.x + size.x / 3,position.y };
		corners_[1] = { position.x + size.x * 2 / 3,position.y };
		corners_[2] = { position.x + size.x,position.y + size.y / 2 };
		corners_[3] = { position.x + size.x * 2 / 3,position.y + size.y };
		corners_[4] = { position.x + size.x / 3,position.y + size.y };
		corners_[5] = { position.x,position.y + size.y / 2 };
		return element.PointInPolygon(point, corners_);
	}
};