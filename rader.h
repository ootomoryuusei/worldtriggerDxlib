#pragma once
#include "Icon.h"
class rader :
    public Icon
{
public:
	rader(GameObject* parent);
	~rader();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	XMFLOAT2 boxPos[2];
	XMFLOAT2 boxSize[2];

};

