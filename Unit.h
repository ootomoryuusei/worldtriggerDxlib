#pragma once
#include "Object2D.h"
class Unit :
    public Object2D
{
public:
	Unit(GameObject* parent);
	~Unit();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	XMFLOAT2 boxPos[2];
	XMFLOAT2 boxSize[2];
};

