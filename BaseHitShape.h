#pragma once
#include"Engine/Transform.h"
#include"Object2D.h"
class BaseHitShape { //“–‚½‚è”»’èŒ`óŠî’êƒNƒ‰ƒX
public :
	virtual ~BaseHitShape() = default;
	virtual void Rebulid(const Transform& tranform) = 0;
	virtual bool IsHit(XMFLOAT2& point,Object2D& element) = 0;
};
