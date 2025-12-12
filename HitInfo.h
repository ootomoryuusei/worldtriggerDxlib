#pragma once
#include<string>

class GameObject;

enum HitTargetType {
	NONE,
	UI,
	OBJECT_3D
};

struct HitInfo {
	HitTargetType type = HitTargetType::NONE; //ヒットした対象の種類
	GameObject* target = nullptr;  			//ヒットしたオブジェクトのポインタ
	float distance = 0.0f; 

	bool IsHit() const { return type != HitTargetType::NONE; }
};