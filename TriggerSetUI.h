#pragma once
#include "Object3D.h"

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
};

