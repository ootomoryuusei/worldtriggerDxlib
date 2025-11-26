#include "RaycastManager.h"

void RaycastManager::CreateRayFromMouse(VECTOR& outOrigin, VECTOR& outDir)
{
	int mx, my;
	GetMousePoint(&mx, &my);

	VECTOR p0 = ConvScreenPosToWorldPos(VGet((float)mx, (float)my, 0.0f));
	VECTOR p1 = ConvScreenPosToWorldPos(VGet((float)mx, (float)my, 1.0f));

	outOrigin = p0;
	outDir = VNorm(p1 - p0);
}

bool RaycastManager::RaycastFromMouse(const vector<Object3D*>& objects, RaycastHit& hit)
{
	VECTOR origin, dir;
	CreateRayFromMouse(origin, dir);

	bool anyHit = false;
	float closeDist = 1e9f;

	for (auto* obj : objects) {
		float dist;
		if (obj->Raycast(origin, dir, dist)) {
			if (dist < closeDist) {
				closeDist = dist;
				hit.object = obj;
				hit.distance = dist;
				anyHit = true;
			}
		}
	}
	return anyHit;
}
