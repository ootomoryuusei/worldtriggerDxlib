#pragma once
#include "Object2D.h"
class rader :
    public Object2D
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

