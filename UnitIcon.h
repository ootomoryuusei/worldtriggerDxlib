#pragma once
#include "Icon.h"
class UnitIcon :
    public Icon
{
public:
	UnitIcon(GameObject* parent);
	~UnitIcon();
	void Update() override;
	/*void Draw() override;*/

private:
};

