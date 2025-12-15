#pragma once
#include"Engine/GameObject.h"
#include"HitInfo.h"
#include<vector>
#include <DxLib.h>

class Object3D;

using std::vector;

class Raycaster3D :
	public GameObject
{
public:
	Raycaster3D(GameObject* parent);
	~Raycaster3D();

	void Initialize() override;
	vector<Object3D*> objects_; // 3Dオブジェクトリスト

	// Object を登録
	void Register(Object3D* object);
	// Object を削除
	void Unregister(Object3D* object);
	HitInfo Raycast(const VECTOR& origin, const VECTOR& dir);
};