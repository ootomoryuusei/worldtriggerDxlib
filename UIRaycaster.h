#pragma once
#include<vector>
#include"Object2D.h"
#include"HitInfo.h"

using std::vector;

class UIRaycaster {
public:
	vector<Object2D*> elements_;
	
	HitInfo Raycast(float mx, float my) {
		for (auto* element : elements_) {
			if (element->IsInMousePoint({ mx, my })) {
				HitInfo info;
				info.type = HitTargetType::UI;
				info.target = element;
				info.distance = 0;
				return info;
			}
		}
		return HitInfo();
	}
};