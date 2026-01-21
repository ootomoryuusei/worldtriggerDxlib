#pragma once
#include"Object2D.h"
class HitSquare : public BaseHitShape { //四角形当たり判定形状クラス
public:
	void Rebulid(const Transform& tranform) override {
	}
	bool IsHit(const XMFLOAT2& point, Object2D& element) override {
		return element.IsInMousePoint(point);
	}
	
	void DrawJudgmentRange(Object2D& element) override {
		OBJ_SIZE_F hitSize = element.GetHitSizeF();
		XMFLOAT3 position = element.GetPosition();
		XMFLOAT2 boxCorners[4] = {
			{position.x, position.y}, // 左上
			{position.x + hitSize.x, position.y}, // 右上
			{position.x + hitSize.x, position.y + hitSize.y}, // 右下
			{position.x, position.y + hitSize.y}  // 左下
		};
		// 四角形描画
		for (int i = 0; i < 4; i++) {
			int j = (i + 1) % 4;
			DrawLineAA(boxCorners[i].x, boxCorners[i].y,
				boxCorners[j].x, boxCorners[j].y,
				GetColor(255, 0, 0), FALSE);
		}
		for (int i = 0; i < 4; ++i) {
			DrawCircle(boxCorners[i].x, boxCorners[i].y, 2, GetColor(0, 255, 0)); // 四隅のマーク
		}
	}
};