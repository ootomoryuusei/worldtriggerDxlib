#pragma once
#include"Object3D.h"
#include"HitInfo.h"
#include<vector>

using std::vector;

class Raycaster3D
{
public:
	vector<Object3D*> objects_; // 3Dオブジェクトリスト

	// Object を登録
	void Register(Object3D* object) {
		objects_.push_back(object);
	}

	// Object を削除
	void Unregister(Object3D* object) {
		objects_.erase(
			remove(objects_.begin(), objects_.end(), object),
			objects_.end()
		);
	}

	HitInfo Raycast(const VECTOR& origin, const VECTOR& dir) {
		HitInfo top_hit;
		float top_dist = 1e9f;

		for (auto& obj : objects_) {
			float dist;
			if (obj->Raycast(origin, dir, dist)) {
				if (dist < top_dist) {
					top_dist = dist;
					top_hit.type = HitTargetType::OBJECT_3D;
					top_hit.target = obj;
					top_hit.distance = dist;
				}
			}
		}
		return top_hit;
	}
};