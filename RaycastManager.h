#pragma once
#include"DxLib.h"
#include"Object3D.h"
#include"HitInfo.h"
#include<vector>

using std::vector;

class RaycastManager
{
public:
	vector<Object3D*> objects_; // 3Dオブジェクトリスト

	HitInfo Raycast(const VECTOR& origin,const VECTOR& dir) {
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

