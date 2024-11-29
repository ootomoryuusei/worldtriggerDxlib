#pragma once
#include "Object3D.h"
class Player1 :
    public Object3D
{
public:
	Player1(GameObject* parent);
	~Player1();
	void Update() override;
	void Draw() override;

	MATRIX ChangeFLOAT3ToMATRIX(FLOAT3 pos, FLOAT3 rot);
private:
	int hBlade; // サーベルモデルのデータ
};

