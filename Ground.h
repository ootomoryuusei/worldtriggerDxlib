#pragma once
#include "Object3D.h"

class Ground : public Object3D
{
public:
	Ground(GameObject* parent);
	~Ground();

	/// <summary>
	/// �����ƃ��f���Ƃ̓����蔻��
	/// </summary>
	/// <param name="begin">�����̎n�_</param>
	/// <param name="end">�����̏I�_</param>
	/// <param name="hit">���������ꍇ�Ɍ�_������ꏊ</param>
	/// <returns>�������Ă����true</returns>
	bool CheckRayCollision(const VECTOR& begin, const VECTOR& end, VECTOR* hit = nullptr);
};