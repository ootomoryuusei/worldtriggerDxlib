#pragma once
#include<string>

enum HitTargetType {
	NONE,
	UI,
	OBJECT_3D
};

struct HitInfo {
	HitTargetType type = HitTargetType::NONE;
	void* target = nullptr;  
	float distance = 0.0f; 

	bool IsHit() const { return type != HitTargetType::NONE; }
};