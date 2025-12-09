#pragma once
#include"Engine/GameObject.h"
#include"Raycaster2D.h"
#include"Raycaster3D.h"

class RaycastManager : public GameObject
{
public:
	RaycastManager(GameObject* parent);
	~RaycastManager();

	void Initialize() override;

	HitInfo RaycastFromMouse(float mx, float my, const VECTOR& rayOrigin, const VECTOR& rayDir) {
		HitInfo hit;
		hit = raycaster2D_->Raycast(mx, my);
		if (hit.IsHit()) return hit;

		hit = raycaster3D_->Raycast(rayOrigin, rayDir);
		if (hit.IsHit()) return hit;

		return hit;
	}
private:
	Raycaster2D* raycaster2D_;
	Raycaster3D* raycaster3D_;
};

