#pragma once
#include "Icon.h"
class MoveTypesIcon :
    public Icon
{
public:
	MoveTypesIcon(GameObject* parent);
	~MoveTypesIcon();
	void Update() override;
	void Draw() override;
private:
	string iconName;
	XMFLOAT2 space;
};

