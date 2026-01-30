#pragma once
#include"Engine/Transform.h"
#include"Object2D.h"
#include"GameInfo.h"
class BaseHitShape { //“–‚½‚è”»’èŒ`óŠî’êƒNƒ‰ƒX
protected:
	vector<XMFLOAT2> corners_;
	size_t cornersNum_;
public :
	virtual ~BaseHitShape() = default;
	virtual void Rebuild(Object2D& element) = 0;
	virtual bool IsHit(const XMFLOAT2& point, Object2D& element) = 0;
	virtual void DrawJudgmentRange(Object2D& element) = 0;
};
