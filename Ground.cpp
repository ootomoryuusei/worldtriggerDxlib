#include "Ground.h"

Ground::Ground(GameObject* parent) : Object3D(parent)
{
	LoadModel("Assets/Stage/Stage00.mv1");
	transform_.position_ = {0,0,0};
	transform_.rotate_ = { 0,0,0 };
}

Ground::~Ground()
{
	if (hModel_ > 0) {
		MV1DeleteModel(hModel_);
		hModel_ = -1;
	}
}

bool Ground::CheckRayCollision(const VECTOR& begin, const VECTOR& end, VECTOR* hit)
{
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel_, 0, begin, end);
	if (ret.HitFlag != 0) {
		if (hit != nullptr) {
			*hit = ret.HitPosition;
		}
		return true;
	}
	return false;
}
