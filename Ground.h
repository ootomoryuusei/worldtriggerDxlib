#pragma once
#include "Object3D.h"

class Ground : public Object3D
{
public:
	Ground(GameObject* parent);
	~Ground();

	/// <summary>
	/// 線分とモデルとの当たり判定
	/// </summary>
	/// <param name="begin">線分の始点</param>
	/// <param name="end">線分の終点</param>
	/// <param name="hit">当たった場合に交点を入れる場所</param>
	/// <returns>あたっていればtrue</returns>
	bool CheckRayCollision(const VECTOR& begin, const VECTOR& end, VECTOR* hit = nullptr);
};