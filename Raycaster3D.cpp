#include<algorithm>
#include "Raycaster3D.h"
#include"Object3D.h"

using std::remove;

Raycaster3D::Raycaster3D(GameObject* parent) : GameObject(parent,"Raycaster3D")
{
}

Raycaster3D::~Raycaster3D()
{
}

void Raycaster3D::Initialize()
{
}

void Raycaster3D::Register(Object3D* object)
{
	objects_.push_back(object);
}

void Raycaster3D::Unregister(Object3D* object)
{
	objects_.erase(
		remove(objects_.begin(), objects_.end(), object),
		objects_.end()
	);
}

HitInfo Raycaster3D::Raycast(const VECTOR& origin, const VECTOR& dir)
{
	HitInfo top_hit;
	float top_dist = 1e9f;

	for (auto& obj : objects_) {
		float dist;

		if (!obj->IsVisibled()) continue; //非表示ならスキップ

		if (obj->Raycast(origin, dir, dist)) {
			if (dist < top_dist) {
				top_dist = dist;
				top_hit.type = HitTargetType::OBJECT_3D;
				top_hit.target = (GameObject*)obj;
				top_hit.distance = dist;
			}
		}
	}
	return top_hit;
}
