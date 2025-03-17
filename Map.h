#pragma once
#include "Icon.h"
class Map :
    public Icon
{
public:
	Map(GameObject* parent);
	~Map();
	void Update() override;
private:
};

