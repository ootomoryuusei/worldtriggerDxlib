#pragma once
#include "Icon.h"
#include<array>

using std::array;

class TriggerArcIcon :
    public Icon
{
public:
	TriggerArcIcon(GameObject* parent);
	~TriggerArcIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	
	const auto& GetBoxCorners() const { return boxCorners; }

	const float GetPercent() { return percent; }
	const float GetStartPercent() { return startPercent; }

	void SetAngle(XMFLOAT2 _angle) { angle.push_back(_angle); }
private:
	float percent;
	float startPercent;
	VECTOR prevVec;
	XMFLOAT2 center;
	array<XMFLOAT2, 4> boxCorners{};

	vector<XMFLOAT2> angle;
	void calculateArc();
};

