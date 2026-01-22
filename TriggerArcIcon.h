#pragma once
#include "ArcIcon.h"
#include<array>
#include<deque>

class TriggerData;
class GroupManager;
class TileIcons;

using std::array;
using std::deque;

class TriggerArcIcon :
    public ArcIcon
{
public:
	TriggerArcIcon(GameObject* parent);
	~TriggerArcIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void DeviceEvent(const DragEvent& event) override;

	void SetAngle(XMFLOAT2 _angle) { angle.push_back(_angle); }

	const auto& GetpData()const { return pData_; }
	void SetHand(HANDS _hand) { hand_ = _hand; }
private:
	VECTOR prevVec;
	XMFLOAT2 center;
	array<XMFLOAT2, 4> boxCorners{};

	vector<XMFLOAT2> angle;
	deque<XMFLOAT2> dq_angle;
	HANDS hand_;

	GroupManager* pGroupManager_;
	TileIcons* pTileIcons_;
	TriggerData* pData_;
	bool firstSet;
	bool moveing;

	float totalTime;
	float elapsedTime;

	void calculateArc();
};

