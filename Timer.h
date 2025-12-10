#pragma once
#include "Object2D.h"
class Timer :
    public Object2D
{
public:
	Timer(GameObject* parent);
	~Timer();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void DeviceEvent(const DoubleClickEvent& event) override;
private:
	XMFLOAT2 boxSize;
};

