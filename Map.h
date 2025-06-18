#pragma once
#include "Icon.h"
class Map :
    public Icon
{
public:
	Map(GameObject* parent);
	~Map();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	XMFLOAT2 GetBoxSize(int _num) { return boxSize[_num]; }
private:
	XMFLOAT2 boxPos[2];
	XMFLOAT2 boxSize[2];
};

