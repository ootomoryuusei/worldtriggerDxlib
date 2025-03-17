#pragma once
#include "Icon.h"
class Unit :
    public Icon
{
public:
	Unit(GameObject* parent);
	~Unit();
	void Update() override;
private:
};

