#pragma once
#include "Object3D.h"
class ShealdIcon :
    public Object3D
{
public:
	ShealdIcon(GameObject* parent);
	~ShealdIcon();
	void Update() override;
	void Draw() override;
private:
	SIZE_2D graphSize_; //�A�C�R���̉摜�T�C�Y
};

