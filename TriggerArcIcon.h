#pragma once
#include "Icon.h"
#include<array>
#include<deque>

class TriggerData;

using std::array;
using std::deque;

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

	const auto& GetpData()const { return pData_; }
	void SetHand(HANDS _hand) { hand_ = _hand; }
private:
	float percent;
	float startPercent;
	VECTOR prevVec;
	XMFLOAT2 center;
	array<XMFLOAT2, 4> boxCorners{};

	vector<XMFLOAT2> angle;
	deque<XMFLOAT2> dq_angle;
	HANDS hand_;

	TriggerData* pData_;
	bool firstSet;
	bool moveing;

	float totalTime;
	float elapsedTime;

	void calculateArc();
};

