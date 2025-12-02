#pragma once
#include "Icon.h"
class Unit :
    public Icon
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

	void DeviceEvent(const MouseClickEvent& event) override;
};

