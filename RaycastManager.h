#pragma once
#include"DxLib.h"
#include"Object3D.h"
#include<vector>

using std::vector;

class RaycastHit {
public:
	Object3D* object = nullptr; //ヒットオブジェクト
	float distance = 0.0f; //距離
};

class RaycastManager
{
public:
	static void CreateRayFromMouse(VECTOR& outOrigin, VECTOR& outDir);

	static bool RaycastFromMouse(const vector<Object3D*>& objects, RaycastHit& hit);
};

