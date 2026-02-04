#pragma once
#include"Object2D.h"
#include"TriggersArcIcon.h"
#include<deque>

class Trigger;
class MoveMentsLoad;
class GroupManager;
class TileIcons;

using std::deque;


class UnitIcon :
    public Object2D
{
public:
	UnitIcon(GameObject* parent);
	~UnitIcon();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void DeviceEvent(const ClickEvent& event) override;
	void DeviceEvent(const DoubleClickEvent& event) override;
	void DeviceEvent(const DragEvent& event) override;

	const auto& GetMoveMent() const{ return moveMent; }
	void AddMoveMent(VECTOR _moveMent, string _movename) { moveMent.push_back({ _moveMent,_movename }); }

	void SetMyTrigger(MYTRIGGER _myTrigger) { myTrigger = _myTrigger; }
	bool GetSet() { return set; }

	const auto& GetpTriggersArcIcon() { return pArcs_; }
	const auto& GetpMoveMentLoad() { return pLoad_; }
private:

	vector<MOVEMENT> moveMent;
	deque<MOVEMENT> dq_moveMent;

	array<Trigger*, static_cast<size_t>(HANDS::MAX)> hands_;

	bool firstSet;
	bool moveing;

	int maxMoveMent;

	float totalTime;
	float elapsedTime;

	MYTRIGGER myTrigger;
	bool set;

	GroupManager* pGroupManager_;
	TileIcons* pTileIcons_;
	TriggersArcIcon* pArcs_;
	MoveMentsLoad* pLoad_;
};

