#pragma once
#include "Object3D.h"

class Camera : public Object3D {
public:
	Camera(GameObject* parent);
	~Camera();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �J�����U�����J�n����
	/// </summary>
	/// <param name="v">�Ռ��̕���</param>
	void Vibration(VECTOR v);

private:
	VECTOR lookTarget;
	float vibTimer;	// ���Ԃ𑪂�ϐ�
	VECTOR vibParam; // �����Ŏw�肳�ꂽ�l
	// �h�ꕝ�����ϐ�
	// �h��ʂ����ϐ�
	VECTOR vibValue; // ���̒l��������
};