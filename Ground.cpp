#include "Ground.h"

Ground::Ground(GameObject* parent) : Object3D(parent)
{
	hModel = MV1LoadModel("Assets/Stage/Stage00.mv1");
	assert(hModel > 0);
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
}

Ground::~Ground()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

bool Ground::CheckRayCollision(const VECTOR& begin, const VECTOR& end, VECTOR* hit)
{
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel, 0, begin, end);
	if (ret.HitFlag != 0) {
		if (hit != nullptr) {
			*hit = ret.HitPosition;
		}
		return true;
	}
	return false;
}
