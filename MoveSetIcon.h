#pragma once
#include "Icon.h"
class MoveSetIcon :
    public Icon
{
public:
	MoveSetIcon(GameObject* parent);
	~MoveSetIcon();
	void Update() override;
	void Draw() override;
private:
	string iconName;
	XMFLOAT2 space;
};

