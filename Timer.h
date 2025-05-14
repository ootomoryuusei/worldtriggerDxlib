#pragma once
#include "Icon.h"
class Timer :
    public Icon
{
public:
	Timer(GameObject* parent);
	~Timer();
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	XMFLOAT2 boxSize;
};

