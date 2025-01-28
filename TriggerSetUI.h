#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;

class TriggerSetUI :
    public Object3D
{
public:
	TriggerSetUI(GameObject* parent);
	~TriggerSetUI();
	void Update() override;
	void Draw() override;
private:
	SIZE_2D graphSize_; //�A�C�R���̉摜�T�C�Y
	SIZE_2D SIFgraphSize; //�L�����N�^�[�Z���N�gUI�̉摜�T�C�Y
	vector<XMFLOAT2> SIUFPosition_;
	int hSlIcUIFrame_;
};

